#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct TYPE_3__ {scalar_t__ bitmap; int /*<<< orphan*/  nls_disk; int /*<<< orphan*/  nls_io; int /*<<< orphan*/  alt_mdb_bh; int /*<<< orphan*/  mdb_bh; int /*<<< orphan*/  cat_tree; int /*<<< orphan*/  ext_tree; } ;

/* Variables and functions */
 TYPE_1__* HFS_SB (struct super_block*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  hfs_btree_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 

void hfs_mdb_put(struct super_block *sb)
{
	if (!HFS_SB(sb))
		return;
	/* free the B-trees */
	hfs_btree_close(HFS_SB(sb)->ext_tree);
	hfs_btree_close(HFS_SB(sb)->cat_tree);

	/* free the buffers holding the primary and alternate MDBs */
	brelse(HFS_SB(sb)->mdb_bh);
	brelse(HFS_SB(sb)->alt_mdb_bh);

	unload_nls(HFS_SB(sb)->nls_io);
	unload_nls(HFS_SB(sb)->nls_disk);

	free_pages((unsigned long)HFS_SB(sb)->bitmap, PAGE_SIZE < 8192 ? 1 : 0);
	kfree(HFS_SB(sb));
	sb->s_fs_info = NULL;
}