#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct omfs_inode {scalar_t__ i_type; int /*<<< orphan*/  i_name; int /*<<< orphan*/  i_sibling; int /*<<< orphan*/  i_head; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int /*<<< orphan*/  f_pos; TYPE_1__* f_dentry; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int (* filldir_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 unsigned char DT_DIR ; 
 unsigned char DT_REG ; 
 scalar_t__ OMFS_DIR ; 
 int /*<<< orphan*/  OMFS_NAMELEN ; 
 int /*<<< orphan*/  OMFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clus_to_blk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omfs_is_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strnlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omfs_fill_chain(struct file *filp, void *dirent, filldir_t filldir,
		u64 fsblock, int hindex)
{
	struct inode *dir = filp->f_dentry->d_inode;
	struct buffer_head *bh;
	struct omfs_inode *oi;
	u64 self;
	int res = 0;
	unsigned char d_type;

	/* follow chain in this bucket */
	while (fsblock != ~0) {
		bh = sb_bread(dir->i_sb, clus_to_blk(OMFS_SB(dir->i_sb),
				fsblock));
		if (!bh)
			goto out;

		oi = (struct omfs_inode *) bh->b_data;
		if (omfs_is_bad(OMFS_SB(dir->i_sb), &oi->i_head, fsblock)) {
			brelse(bh);
			goto out;
		}

		self = fsblock;
		fsblock = be64_to_cpu(oi->i_sibling);

		/* skip visited nodes */
		if (hindex) {
			hindex--;
			brelse(bh);
			continue;
		}

		d_type = (oi->i_type == OMFS_DIR) ? DT_DIR : DT_REG;

		res = filldir(dirent, oi->i_name, strnlen(oi->i_name,
			OMFS_NAMELEN), filp->f_pos, self, d_type);
		if (res == 0)
			filp->f_pos++;
		brelse(bh);
	}
out:
	return res;
}