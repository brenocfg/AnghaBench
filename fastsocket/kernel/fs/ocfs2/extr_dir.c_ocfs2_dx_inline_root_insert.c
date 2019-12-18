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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_entries; } ;
struct ocfs2_dx_hinfo {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_dx_entry_list_insert (int /*<<< orphan*/ *,struct ocfs2_dx_hinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_dx_inline_root_insert(struct inode *dir, handle_t *handle,
					struct ocfs2_dx_hinfo *hinfo,
					u64 dirent_blk,
					struct ocfs2_dx_root_block *dx_root)
{
	ocfs2_dx_entry_list_insert(&dx_root->dr_entries, hinfo, dirent_blk);
}