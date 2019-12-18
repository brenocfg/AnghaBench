#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_iget_args {unsigned long dirid; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct TYPE_3__ {unsigned long k_dir_id; scalar_t__ k_type; scalar_t__ k_offset; int /*<<< orphan*/  k_objectid; } ;
struct cpu_key {TYPE_1__ on_disk_key; int /*<<< orphan*/  version; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_is_unlinked_ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  INITIALIZE_PATH (int /*<<< orphan*/ ) ; 
 int IO_ERROR ; 
 int ITEM_FOUND ; 
 int /*<<< orphan*/  KEY_FORMAT_3_5 ; 
 TYPE_2__* REISERFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_to_sd ; 
 int /*<<< orphan*/  pathrelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_check_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_error (int /*<<< orphan*/ ,char*,char*,struct cpu_key*) ; 
 int /*<<< orphan*/  reiserfs_make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*,struct cpu_key*) ; 
 int search_item (int /*<<< orphan*/ ,struct cpu_key*,int /*<<< orphan*/ *) ; 

void reiserfs_read_locked_inode(struct inode *inode,
				struct reiserfs_iget_args *args)
{
	INITIALIZE_PATH(path_to_sd);
	struct cpu_key key;
	unsigned long dirino;
	int retval;

	dirino = args->dirid;

	/* set version 1, version 2 could be used too, because stat data
	   key is the same in both versions */
	key.version = KEY_FORMAT_3_5;
	key.on_disk_key.k_dir_id = dirino;
	key.on_disk_key.k_objectid = inode->i_ino;
	key.on_disk_key.k_offset = 0;
	key.on_disk_key.k_type = 0;

	/* look for the object's stat data */
	retval = search_item(inode->i_sb, &key, &path_to_sd);
	if (retval == IO_ERROR) {
		reiserfs_error(inode->i_sb, "vs-13070",
			       "i/o failure occurred trying to find "
			       "stat data of %K", &key);
		reiserfs_make_bad_inode(inode);
		return;
	}
	if (retval != ITEM_FOUND) {
		/* a stale NFS handle can trigger this without it being an error */
		pathrelse(&path_to_sd);
		reiserfs_make_bad_inode(inode);
		inode->i_nlink = 0;
		return;
	}

	init_inode(inode, &path_to_sd);

	/* It is possible that knfsd is trying to access inode of a file
	   that is being removed from the disk by some other thread. As we
	   update sd on unlink all that is required is to check for nlink
	   here. This bug was first found by Sizif when debugging
	   SquidNG/Butterfly, forgotten, and found again after Philippe
	   Gramoulle <philippe.gramoulle@mmania.com> reproduced it.

	   More logical fix would require changes in fs/inode.c:iput() to
	   remove inode from hash-table _after_ fs cleaned disk stuff up and
	   in iget() to return NULL if I_FREEING inode is found in
	   hash-table. */
	/* Currently there is one place where it's ok to meet inode with
	   nlink==0: processing of open-unlinked and half-truncated files
	   during mount (fs/reiserfs/super.c:finish_unfinished()). */
	if ((inode->i_nlink == 0) &&
	    !REISERFS_SB(inode->i_sb)->s_is_unlinked_ok) {
		reiserfs_warning(inode->i_sb, "vs-13075",
				 "dead inode read from disk %K. "
				 "This is likely to be race with knfsd. Ignore",
				 &key);
		reiserfs_make_bad_inode(inode);
	}

	reiserfs_check_path(&path_to_sd);	/* init inode should be relsing */

}