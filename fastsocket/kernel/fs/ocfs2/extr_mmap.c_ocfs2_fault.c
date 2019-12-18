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
struct vm_fault {int /*<<< orphan*/  page; int /*<<< orphan*/  pgoff; } ;
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int VM_FAULT_SIGBUS ; 
 int filemap_fault (struct vm_area_struct*,struct vm_fault*) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_ptr (int /*<<< orphan*/ ) ; 
 int ocfs2_vm_op_block_sigs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ocfs2_vm_op_unblock_sigs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_fault(struct vm_area_struct *area, struct vm_fault *vmf)
{
	sigset_t blocked, oldset;
	int error, ret;

	mlog_entry("(area=%p, page offset=%lu)\n", area, vmf->pgoff);

	error = ocfs2_vm_op_block_sigs(&blocked, &oldset);
	if (error < 0) {
		mlog_errno(error);
		ret = VM_FAULT_SIGBUS;
		goto out;
	}

	ret = filemap_fault(area, vmf);

	error = ocfs2_vm_op_unblock_sigs(&oldset);
	if (error < 0)
		mlog_errno(error);
out:
	mlog_exit_ptr(vmf->page);
	return ret;
}