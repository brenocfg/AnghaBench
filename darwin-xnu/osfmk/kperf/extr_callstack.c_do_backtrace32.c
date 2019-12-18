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
struct TYPE_6__ {scalar_t__ ebp; scalar_t__ eip; } ;
typedef  TYPE_1__ x86_saved_state32_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  unsigned long uint32_t ;
typedef  TYPE_2__* thread_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {int /*<<< orphan*/  prev; int /*<<< orphan*/  caller; } ;
typedef  TYPE_3__ cframe_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {scalar_t__ kernel_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ VALID_STACK_ADDRESS (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  chudxnu_kern_read (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chudxnu_task_read (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ chudxnu_vm_unslide (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_stack_size ; 

__attribute__((used)) static kern_return_t do_backtrace32(
	task_t task,
	thread_t thread,
	x86_saved_state32_t *regs, 
	uint64_t *frames,
	mach_msg_type_number_t *start_idx,
	mach_msg_type_number_t max_idx,
	boolean_t supervisor)
{
	uint32_t tmpWord = 0UL;
	uint64_t currPC = (uint64_t) regs->eip;
	uint64_t currFP = (uint64_t) regs->ebp;
	uint64_t prevPC = 0ULL;
	uint64_t prevFP = 0ULL;
	uint64_t kernStackMin = thread->kernel_stack;
    uint64_t kernStackMax = kernStackMin + kernel_stack_size;
	mach_msg_type_number_t ct = *start_idx;
	kern_return_t kr = KERN_FAILURE;

	if(ct >= max_idx)
		return KERN_RESOURCE_SHORTAGE;	// no frames traced
	
	frames[ct++] = chudxnu_vm_unslide(currPC, supervisor);

	// build a backtrace of this 32 bit state.
	while(VALID_STACK_ADDRESS(supervisor, currFP, kernStackMin, kernStackMax)) {
		cframe_t *fp = (cframe_t *) (uintptr_t) currFP;

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
			kr = chudxnu_kern_read(&tmpWord, (vm_offset_t) &fp->caller, sizeof(uint32_t));
		} else {
			kr = chudxnu_task_read(task, &tmpWord, (vm_offset_t) &fp->caller, sizeof(uint32_t));
		}

		if(kr != KERN_SUCCESS) {
			currPC = 0ULL;
			break;
		}

		currPC = (uint64_t) tmpWord;    // promote 32 bit address

        /* 
         * retrive contents of the frame pointer and advance to the next stack
         * frame if it's valid 
         */
        prevFP = 0;
		if(supervisor) {
			kr = chudxnu_kern_read(&tmpWord, (vm_offset_t)&fp->prev, sizeof(uint32_t));
		} else {
			kr = chudxnu_task_read(task, &tmpWord, (vm_offset_t)&fp->prev, sizeof(uint32_t));
		}
		prevFP = (uint64_t) tmpWord;    // promote 32 bit address

        if(prevFP) {
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