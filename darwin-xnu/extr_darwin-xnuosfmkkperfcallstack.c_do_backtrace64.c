#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rip; } ;
struct TYPE_7__ {scalar_t__ rbp; TYPE_1__ isf; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  TYPE_3__* thread_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  kernel_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ VALID_STACK_ADDRESS64 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  chudxnu_kern_read (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chudxnu_task_read (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int) ; 
 scalar_t__ chudxnu_vm_unslide (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_stack_size ; 

__attribute__((used)) static kern_return_t do_backtrace64(
	task_t task,
	thread_t thread,
	x86_saved_state64_t *regs, 
	uint64_t *frames,
	mach_msg_type_number_t *start_idx,
	mach_msg_type_number_t max_idx,
	boolean_t supervisor)
{
	uint64_t currPC = regs->isf.rip;
	uint64_t currFP = regs->rbp;
	uint64_t prevPC = 0ULL;
	uint64_t prevFP = 0ULL;
	uint64_t kernStackMin = (uint64_t)thread->kernel_stack;
    uint64_t kernStackMax = (uint64_t)kernStackMin + kernel_stack_size;
	mach_msg_type_number_t ct = *start_idx;
	kern_return_t kr = KERN_FAILURE;

	if(*start_idx >= max_idx)
		return KERN_RESOURCE_SHORTAGE;	// no frames traced
	
	frames[ct++] = chudxnu_vm_unslide(currPC, supervisor);

	// build a backtrace of this 32 bit state.
	while(VALID_STACK_ADDRESS64(supervisor, currFP, kernStackMin, kernStackMax)) {
		// this is the address where caller lives in the user thread
		uint64_t caller = currFP + sizeof(uint64_t);

        if(!currFP) {
            currPC = 0;
            break;
        }

        if(ct >= max_idx) {
			*start_idx = ct;
            return KERN_RESOURCE_SHORTAGE;
        }

		/* read our caller */
		if(supervisor) {
			kr = chudxnu_kern_read(&currPC, (vm_offset_t)caller, sizeof(uint64_t));
		} else {
			kr = chudxnu_task_read(task, &currPC, caller, sizeof(uint64_t));
		}

		if(kr != KERN_SUCCESS) {
			currPC = 0ULL;
			break;
		}

        /* 
         * retrive contents of the frame pointer and advance to the next stack
         * frame if it's valid 
         */
        prevFP = 0;
		if(supervisor) {
			kr = chudxnu_kern_read(&prevFP, (vm_offset_t)currFP, sizeof(uint64_t));
		} else {
			kr = chudxnu_task_read(task, &prevFP, currFP, sizeof(uint64_t));
		}

        if(VALID_STACK_ADDRESS64(supervisor, prevFP, kernStackMin, kernStackMax)) {
            frames[ct++] = chudxnu_vm_unslide(currPC, supervisor);
            prevPC = currPC;
        }
        if(prevFP < currFP) {
            break;
        } else {
            currFP = prevFP;
        }	
	}

	*start_idx = ct;
	return KERN_SUCCESS;
}