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
struct super_block {int s_flags; int /*<<< orphan*/ * s_fs_info; scalar_t__ s_dirt; } ;
struct hfsplus_vh {int /*<<< orphan*/  attributes; int /*<<< orphan*/  modify_date; } ;
struct TYPE_2__ {int /*<<< orphan*/  nls; int /*<<< orphan*/  s_vhbh; int /*<<< orphan*/  hidden_dir; int /*<<< orphan*/  alloc_file; int /*<<< orphan*/  ext_tree; int /*<<< orphan*/  cat_tree; struct hfsplus_vh* s_vhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SUPER ; 
 TYPE_1__ HFSPLUS_SB (struct super_block*) ; 
 int /*<<< orphan*/  HFSPLUS_VOL_INCNSTNT ; 
 int /*<<< orphan*/  HFSPLUS_VOL_UNMNT ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hfs_btree_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsp_now2mt () ; 
 int /*<<< orphan*/  hfsplus_write_super (struct super_block*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_dirty_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void hfsplus_put_super(struct super_block *sb)
{
	dprint(DBG_SUPER, "hfsplus_put_super\n");
	if (!sb->s_fs_info)
		return;

	lock_kernel();

	if (sb->s_dirt)
		hfsplus_write_super(sb);
	if (!(sb->s_flags & MS_RDONLY) && HFSPLUS_SB(sb).s_vhdr) {
		struct hfsplus_vh *vhdr = HFSPLUS_SB(sb).s_vhdr;

		vhdr->modify_date = hfsp_now2mt();
		vhdr->attributes |= cpu_to_be32(HFSPLUS_VOL_UNMNT);
		vhdr->attributes &= cpu_to_be32(~HFSPLUS_VOL_INCNSTNT);
		mark_buffer_dirty(HFSPLUS_SB(sb).s_vhbh);
		sync_dirty_buffer(HFSPLUS_SB(sb).s_vhbh);
	}

	hfs_btree_close(HFSPLUS_SB(sb).cat_tree);
	hfs_btree_close(HFSPLUS_SB(sb).ext_tree);
	iput(HFSPLUS_SB(sb).alloc_file);
	iput(HFSPLUS_SB(sb).hidden_dir);
	brelse(HFSPLUS_SB(sb).s_vhbh);
	unload_nls(HFSPLUS_SB(sb).nls);
	kfree(sb->s_fs_info);
	sb->s_fs_info = NULL;

	unlock_kernel();
}