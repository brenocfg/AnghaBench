#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {scalar_t__ s_dev; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_bdev; } ;
struct reiserfs_journal {int /*<<< orphan*/ * j_dev_bd; void* j_dev_mode; } ;
typedef  void* fmode_t ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SB_ONDISK_JOURNAL_DEVICE (struct super_block*) ; 
 int /*<<< orphan*/  __bdevname (scalar_t__,char*) ; 
 int bd_claim (int /*<<< orphan*/ *,struct reiserfs_journal*) ; 
 scalar_t__ bdev_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ new_decode_dev (scalar_t__) ; 
 int /*<<< orphan*/ * open_bdev_exclusive (char const*,void*,struct reiserfs_journal*) ; 
 int /*<<< orphan*/ * open_by_devnum (scalar_t__,void*) ; 
 int /*<<< orphan*/  reiserfs_info (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char const*,int,...) ; 
 int /*<<< orphan*/  set_blocksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int journal_init_dev(struct super_block *super,
			    struct reiserfs_journal *journal,
			    const char *jdev_name)
{
	int result;
	dev_t jdev;
	fmode_t blkdev_mode = FMODE_READ | FMODE_WRITE;
	char b[BDEVNAME_SIZE];

	result = 0;

	journal->j_dev_bd = NULL;
	jdev = SB_ONDISK_JOURNAL_DEVICE(super) ?
	    new_decode_dev(SB_ONDISK_JOURNAL_DEVICE(super)) : super->s_dev;

	if (bdev_read_only(super->s_bdev))
		blkdev_mode = FMODE_READ;

	/* there is no "jdev" option and journal is on separate device */
	if ((!jdev_name || !jdev_name[0])) {
		journal->j_dev_bd = open_by_devnum(jdev, blkdev_mode);
		journal->j_dev_mode = blkdev_mode;
		if (IS_ERR(journal->j_dev_bd)) {
			result = PTR_ERR(journal->j_dev_bd);
			journal->j_dev_bd = NULL;
			reiserfs_warning(super, "sh-458",
					 "cannot init journal device '%s': %i",
					 __bdevname(jdev, b), result);
			return result;
		} else if (jdev != super->s_dev) {
			result = bd_claim(journal->j_dev_bd, journal);
			if (result) {
				blkdev_put(journal->j_dev_bd, blkdev_mode);
				return result;
			}

			set_blocksize(journal->j_dev_bd, super->s_blocksize);
		}

		return 0;
	}

	journal->j_dev_mode = blkdev_mode;
	journal->j_dev_bd = open_bdev_exclusive(jdev_name,
						blkdev_mode, journal);
	if (IS_ERR(journal->j_dev_bd)) {
		result = PTR_ERR(journal->j_dev_bd);
		journal->j_dev_bd = NULL;
		reiserfs_warning(super,
				 "journal_init_dev: Cannot open '%s': %i",
				 jdev_name, result);
		return result;
	}

	set_blocksize(journal->j_dev_bd, super->s_blocksize);
	reiserfs_info(super,
		      "journal_init_dev: journal device: %s\n",
		      bdevname(journal->j_dev_bd, b));
	return 0;
}