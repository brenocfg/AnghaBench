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
struct task_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  context; } ;
struct TYPE_2__ {unsigned long slb_cache_ptr; int /*<<< orphan*/  context; scalar_t__* slb_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_NO_SLBIE_B ; 
 unsigned long KSTK_EIP (struct task_struct*) ; 
 unsigned long KSTK_ESP (struct task_struct*) ; 
 unsigned long SID_SHIFT ; 
 unsigned long SLBIE_C ; 
 unsigned long SLBIE_SSIZE_SHIFT ; 
 unsigned long SLB_CACHE_ENTRIES ; 
 int /*<<< orphan*/  __slb_flush_and_rebolt () ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esids_match (unsigned long,unsigned long) ; 
 TYPE_1__* get_paca () ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 scalar_t__ is_kernel_addr (unsigned long) ; 
 int /*<<< orphan*/  slb_allocate (unsigned long) ; 
 unsigned long user_segment_size (unsigned long) ; 

void switch_slb(struct task_struct *tsk, struct mm_struct *mm)
{
	unsigned long offset;
	unsigned long slbie_data = 0;
	unsigned long pc = KSTK_EIP(tsk);
	unsigned long stack = KSTK_ESP(tsk);
	unsigned long exec_base;

	/*
	 * We need interrupts hard-disabled here, not just soft-disabled,
	 * so that a PMU interrupt can't occur, which might try to access
	 * user memory (to get a stack trace) and possible cause an SLB miss
	 * which would update the slb_cache/slb_cache_ptr fields in the PACA.
	 */
	hard_irq_disable();
	offset = get_paca()->slb_cache_ptr;
	if (!cpu_has_feature(CPU_FTR_NO_SLBIE_B) &&
	    offset <= SLB_CACHE_ENTRIES) {
		int i;
		asm volatile("isync" : : : "memory");
		for (i = 0; i < offset; i++) {
			slbie_data = (unsigned long)get_paca()->slb_cache[i]
				<< SID_SHIFT; /* EA */
			slbie_data |= user_segment_size(slbie_data)
				<< SLBIE_SSIZE_SHIFT;
			slbie_data |= SLBIE_C; /* C set for user addresses */
			asm volatile("slbie %0" : : "r" (slbie_data));
		}
		asm volatile("isync" : : : "memory");
	} else {
		__slb_flush_and_rebolt();
	}

	/* Workaround POWER5 < DD2.1 issue */
	if (offset == 1 || offset > SLB_CACHE_ENTRIES)
		asm volatile("slbie %0" : : "r" (slbie_data));

	get_paca()->slb_cache_ptr = 0;
	get_paca()->context = mm->context;

	/*
	 * preload some userspace segments into the SLB.
	 * Almost all 32 and 64bit PowerPC executables are linked at
	 * 0x10000000 so it makes sense to preload this segment.
	 */
	exec_base = 0x10000000;

	if (is_kernel_addr(pc) || is_kernel_addr(stack) ||
	    is_kernel_addr(exec_base))
		return;

	slb_allocate(pc);

	if (!esids_match(pc, stack))
		slb_allocate(stack);

	if (!esids_match(pc, exec_base) &&
	    !esids_match(stack, exec_base))
		slb_allocate(exec_base);
}