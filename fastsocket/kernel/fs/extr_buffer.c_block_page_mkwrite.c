#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_fault {int dummy; } ;
struct vm_area_struct {TYPE_4__* vm_file; } ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  get_block_t ;
struct TYPE_7__ {TYPE_2__* dentry; } ;
struct TYPE_8__ {TYPE_3__ f_path; } ;
struct TYPE_6__ {TYPE_1__* d_inode; } ;
struct TYPE_5__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_FREEZE_WRITE ; 
 int __block_page_mkwrite (struct vm_area_struct*,struct vm_fault*,int /*<<< orphan*/ ) ; 
 int block_page_mkwrite_return (int) ; 
 int /*<<< orphan*/  sb_end_pagefault (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_new_freeze (struct super_block*) ; 
 int /*<<< orphan*/  sb_start_pagefault (struct super_block*) ; 
 int /*<<< orphan*/  vfs_check_frozen (struct super_block*,int /*<<< orphan*/ ) ; 

int block_page_mkwrite(struct vm_area_struct *vma, struct vm_fault *vmf,
		   get_block_t get_block)
{
	int ret;
	__attribute__ ((unused)) struct super_block *sb = vma->vm_file->f_path.dentry->d_inode->i_sb;

	/*
	 *  OLD FREEZE PATH:
	 * This check is racy but catches the common case. The check in
	 * __block_page_mkwrite() is reliable.
	 */
	if (!sb_has_new_freeze(sb))
		vfs_check_frozen(sb, SB_FREEZE_WRITE);

	sb_start_pagefault(sb);
	ret = __block_page_mkwrite(vma, vmf, get_block);
	sb_end_pagefault(sb);
	return block_page_mkwrite_return(ret);
}