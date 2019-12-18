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
struct vm_area_struct {TYPE_2__* vm_file; } ;
struct hugepage_subpool {int dummy; } ;
struct TYPE_4__ {TYPE_1__* f_dentry; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 struct hugepage_subpool* subpool_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hugepage_subpool *subpool_vma(struct vm_area_struct *vma)
{
	return subpool_inode(vma->vm_file->f_dentry->d_inode);
}