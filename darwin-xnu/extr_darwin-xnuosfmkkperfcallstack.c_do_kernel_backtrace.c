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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* thread_t ;
struct x86_kernel_state {int /*<<< orphan*/  k_rbp; int /*<<< orphan*/  k_rip; } ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  currPC ;
struct TYPE_3__ {int /*<<< orphan*/  kernel_stack; } ;

/* Variables and functions */
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VALID_STACK_ADDRESS64 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ chudxnu_kern_read (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ chudxnu_vm_unslide (scalar_t__,int) ; 
 scalar_t__ kernel_stack_size ; 

__attribute__((used)) static kern_return_t do_kernel_backtrace(
	thread_t thread,
	struct x86_kernel_state *regs, 
	uint64_t *frames,
	mach_msg_type_number_t *start_idx,
	mach_msg_type_number_t max_idx)
{
	uint64_t kernStackMin = (uint64_t)thread->kernel_stack;
    uint64_t kernStackMax = (uint64_t)kernStackMin + kernel_stack_size;
	mach_msg_type_number_t ct = *start_idx;
	kern_return_t kr = KERN_FAILURE;

#if __LP64__
	uint64_t currPC = 0ULL;
	uint64_t currFP = 0ULL;
	uint64_t prevPC = 0ULL;
	uint64_t prevFP = 0ULL;
	if(KERN_SUCCESS != chudxnu_kern_read(&currPC, (vm_offset_t)&(regs->k_rip), sizeof(uint64_t))) {
		return KERN_FAILURE;
	}
	if(KERN_SUCCESS != chudxnu_kern_read(&currFP, (vm_offset_t)&(regs->k_rbp), sizeof(uint64_t))) {
		return KERN_FAILURE;
	}
#else
	uint32_t currPC = 0U;
	uint32_t currFP = 0U;
	uint32_t prevPC = 0U;
	uint32_t prevFP = 0U;
	if(KERN_SUCCESS != chudxnu_kern_read(&currPC, (vm_offset_t)&(regs->k_eip), sizeof(uint32_t))) {
		return KERN_FAILURE;
	}
	if(KERN_SUCCESS != chudxnu_kern_read(&currFP, (vm_offset_t)&(regs->k_ebp), sizeof(uint32_t))) {
		return KERN_FAILURE;
	}
#endif

	if(*start_idx >= max_idx)
		return KERN_RESOURCE_SHORTAGE;	// no frames traced
	
	if(!currPC) {
		return KERN_FAILURE;
	}

	frames[ct++] = chudxnu_vm_unslide((uint64_t)currPC, 1);

	// build a backtrace of this kernel state
#if __LP64__
	while(VALID_STACK_ADDRESS64(TRUE, currFP, kernStackMin, kernStackMax)) {
		// this is the address where caller lives in the user thread
		uint64_t caller = currFP + sizeof(uint64_t);
#else
	while(VALID_STACK_ADDRESS(TRUE, currFP, kernStackMin, kernStackMax)) {
		uint32_t caller = (uint32_t)currFP + sizeof(uint32_t);
#endif

        if(!currFP || !currPC) {
            currPC = 0;
            break;
        }

        if(ct >= max_idx) {
			*start_idx = ct;
            return KERN_RESOURCE_SHORTAGE;
        }

		/* read our caller */
		kr = chudxnu_kern_read(&currPC, (vm_offset_t)caller, sizeof(currPC));

		if(kr != KERN_SUCCESS || !currPC) {
			currPC = 0UL;
			break;
		}

        /* 
         * retrive contents of the frame pointer and advance to the next stack
         * frame if it's valid 
         */
        prevFP = 0;
		kr = chudxnu_kern_read(&prevFP, (vm_offset_t)currFP, sizeof(currPC));

#if __LP64__
        if(VALID_STACK_ADDRESS64(TRUE, prevFP, kernStackMin, kernStackMax)) {
#else
        if(VALID_STACK_ADDRESS(TRUE, prevFP, kernStackMin, kernStackMax)) {
#endif
            frames[ct++] = chudxnu_vm_unslide((uint64_t)currPC, 1);
            prevPC = currPC;
        }
        if(prevFP <= currFP) {
            break;
        } else {
            currFP = prevFP;
        }	
	}

	*start_idx = ct;
	return KERN_SUCCESS;
}