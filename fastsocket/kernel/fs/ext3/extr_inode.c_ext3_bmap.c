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
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int i_state; } ;

/* Variables and functions */
 TYPE_1__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/ * EXT3_JOURNAL (struct inode*) ; 
 int EXT3_STATE_JDATA ; 
 int /*<<< orphan*/  ext3_get_block ; 
 int /*<<< orphan*/  generic_block_bmap (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_unlock_updates (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sector_t ext3_bmap(struct address_space *mapping, sector_t block)
{
	struct inode *inode = mapping->host;
	journal_t *journal;
	int err;

	if (EXT3_I(inode)->i_state & EXT3_STATE_JDATA) {
		/*
		 * This is a REALLY heavyweight approach, but the use of
		 * bmap on dirty files is expected to be extremely rare:
		 * only if we run lilo or swapon on a freshly made file
		 * do we expect this to happen.
		 *
		 * (bmap requires CAP_SYS_RAWIO so this does not
		 * represent an unprivileged user DOS attack --- we'd be
		 * in trouble if mortal users could trigger this path at
		 * will.)
		 *
		 * NB. EXT3_STATE_JDATA is not set on files other than
		 * regular files.  If somebody wants to bmap a directory
		 * or symlink and gets confused because the buffer
		 * hasn't yet been flushed to disk, they deserve
		 * everything they get.
		 */

		EXT3_I(inode)->i_state &= ~EXT3_STATE_JDATA;
		journal = EXT3_JOURNAL(inode);
		journal_lock_updates(journal);
		err = journal_flush(journal);
		journal_unlock_updates(journal);

		if (err)
			return 0;
	}

	return generic_block_bmap(mapping,block,ext3_get_block);
}