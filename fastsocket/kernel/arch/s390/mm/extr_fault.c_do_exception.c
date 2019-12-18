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
struct vm_area_struct {unsigned long vm_start; int vm_flags; } ;
struct task_struct {int /*<<< orphan*/  min_flt; int /*<<< orphan*/  maj_flt; struct mm_struct* mm; } ;
struct pt_regs {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_FLAG_WRITE ; 
 unsigned long HPAGE_MASK ; 
 int /*<<< orphan*/  PERF_COUNT_SW_PAGE_FAULTS ; 
 int /*<<< orphan*/  PERF_COUNT_SW_PAGE_FAULTS_MAJ ; 
 int /*<<< orphan*/  PERF_COUNT_SW_PAGE_FAULTS_MIN ; 
 int /*<<< orphan*/  TIF_SINGLE_STEP ; 
 int VM_FAULT_BADACCESS ; 
 int VM_FAULT_BADCONTEXT ; 
 int VM_FAULT_BADMAP ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_MAJOR ; 
 int VM_GROWSDOWN ; 
 int VM_WRITE ; 
 unsigned long __FAIL_ADDR_MASK ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ expand_stack (struct vm_area_struct*,unsigned long) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int handle_mm_fault (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ in_atomic () ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ notify_page_fault (struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_space_fault (unsigned long) ; 

__attribute__((used)) static inline int do_exception(struct pt_regs *regs, int access,
			       unsigned long trans_exc_code)
{
	struct task_struct *tsk;
	struct mm_struct *mm;
	struct vm_area_struct *vma;
	unsigned long address;
	int fault;

	if (notify_page_fault(regs))
		return 0;

	tsk = current;
	mm = tsk->mm;

	/*
	 * Verify that the fault happened in user space, that
	 * we are not in an interrupt and that there is a 
	 * user context.
	 */
	fault = VM_FAULT_BADCONTEXT;
	if (unlikely(!user_space_fault(trans_exc_code) || in_atomic() || !mm))
		goto out;

	address = trans_exc_code & __FAIL_ADDR_MASK;
	/*
	 * When we get here, the fault happened in the current
	 * task's user address space, so we can switch on the
	 * interrupts again and then search the VMAs
	 */
	local_irq_enable();
	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);
	down_read(&mm->mmap_sem);

	fault = VM_FAULT_BADMAP;
	vma = find_vma(mm, address);
	if (!vma)
		goto out_up;

	if (unlikely(vma->vm_start > address)) {
		if (!(vma->vm_flags & VM_GROWSDOWN))
			goto out_up;
		if (expand_stack(vma, address))
			goto out_up;
	}

	/*
	 * Ok, we have a good vm_area for this memory access, so
	 * we can handle it..
	 */
	fault = VM_FAULT_BADACCESS;
	if (unlikely(!(vma->vm_flags & access)))
		goto out_up;

	if (is_vm_hugetlb_page(vma))
		address &= HPAGE_MASK;
	/*
	 * If for any reason at all we couldn't handle the fault,
	 * make sure we exit gracefully rather than endlessly redo
	 * the fault.
	 */
	fault = handle_mm_fault(mm, vma, address,
				(access == VM_WRITE) ? FAULT_FLAG_WRITE : 0);
	if (unlikely(fault & VM_FAULT_ERROR))
		goto out_up;

	if (fault & VM_FAULT_MAJOR) {
		tsk->maj_flt++;
		perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1,
				     regs, address);
	} else {
		tsk->min_flt++;
		perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1,
				     regs, address);
	}
	/*
	 * The instruction that caused the program check will
	 * be repeated. Don't signal single step via SIGTRAP.
	 */
	clear_tsk_thread_flag(tsk, TIF_SINGLE_STEP);
	fault = 0;
out_up:
	up_read(&mm->mmap_sem);
out:
	return fault;
}