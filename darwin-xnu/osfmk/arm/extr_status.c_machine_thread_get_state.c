#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* thread_t ;
typedef  int* thread_state_t ;
typedef  int thread_flavor_t ;
struct arm_vfpsaved_state {int /*<<< orphan*/ * r; int /*<<< orphan*/  fpscr; } ;
struct arm_vfp_state {int /*<<< orphan*/ * r; int /*<<< orphan*/  fpscr; } ;
struct arm_thread_state {int /*<<< orphan*/  sp; int /*<<< orphan*/ * r; int /*<<< orphan*/  pc; int /*<<< orphan*/  cpsr; int /*<<< orphan*/  lr; } ;
struct arm_saved_state {int /*<<< orphan*/  far; int /*<<< orphan*/  fsr; int /*<<< orphan*/  exception; int /*<<< orphan*/ * r; int /*<<< orphan*/  cpsr; int /*<<< orphan*/  pc; int /*<<< orphan*/  lr; int /*<<< orphan*/  sp; } ;
struct arm_exception_state {int /*<<< orphan*/  far; int /*<<< orphan*/  fsr; int /*<<< orphan*/  exception; } ;
typedef  int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {int /*<<< orphan*/  count; int /*<<< orphan*/  flavor; } ;
struct TYPE_11__ {TYPE_1__ ash; struct arm_thread_state ts_32; } ;
typedef  TYPE_4__ arm_unified_thread_state_t ;
typedef  int /*<<< orphan*/  arm_debug_state_t ;
struct TYPE_9__ {struct arm_saved_state PcbData; } ;
struct TYPE_10__ {TYPE_2__ machine; } ;

/* Variables and functions */
#define  ARM_DEBUG_STATE 132 
 int ARM_DEBUG_STATE_COUNT ; 
#define  ARM_EXCEPTION_STATE 131 
 int ARM_EXCEPTION_STATE_COUNT ; 
#define  ARM_THREAD_STATE 130 
 int /*<<< orphan*/  ARM_THREAD_STATE32 ; 
 int /*<<< orphan*/  ARM_THREAD_STATE32_COUNT ; 
 int ARM_THREAD_STATE_COUNT ; 
 int ARM_UNIFIED_THREAD_STATE_COUNT ; 
 int ARM_VFPV2_STATE_COUNT ; 
#define  ARM_VFP_STATE 129 
 int ARM_VFP_STATE_COUNT ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  THREAD_STATE_FLAVOR_LIST 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * find_debug_state (TYPE_3__*) ; 
 struct arm_vfpsaved_state* find_user_vfp (TYPE_3__*) ; 
 int /*<<< orphan*/  machine_thread_get_state_kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
machine_thread_get_state(
			 thread_t thread,
			 thread_flavor_t flavor,
			 thread_state_t tstate,
			 mach_msg_type_number_t * count)
{

#define machine_thread_get_state_kprintf(x...)	/* kprintf("machine_thread_get
						 * _state: " x) */

	switch (flavor) {
	case THREAD_STATE_FLAVOR_LIST:
		if (*count < 4)
			return (KERN_INVALID_ARGUMENT);

		tstate[0] = ARM_THREAD_STATE;
		tstate[1] = ARM_VFP_STATE;
		tstate[2] = ARM_EXCEPTION_STATE;
		tstate[3] = ARM_DEBUG_STATE;
		*count = 4;
		break;

	case ARM_THREAD_STATE:{
			struct arm_thread_state *state;
			struct arm_saved_state *saved_state;
			arm_unified_thread_state_t *unified_state;

			unsigned int    i;
			if (*count < ARM_THREAD_STATE_COUNT)
				return (KERN_INVALID_ARGUMENT);

			if (*count == ARM_UNIFIED_THREAD_STATE_COUNT) {
				unified_state = (arm_unified_thread_state_t *) tstate;
				state = &unified_state->ts_32;
				unified_state->ash.flavor = ARM_THREAD_STATE32;
				unified_state->ash.count = ARM_THREAD_STATE32_COUNT;
			} else {
				state = (struct arm_thread_state *) tstate;
			}
			saved_state = &thread->machine.PcbData;

			state->sp = saved_state->sp;
			state->lr = saved_state->lr;
			state->pc = saved_state->pc;
			state->cpsr = saved_state->cpsr;
			for (i = 0; i < 13; i++)
				state->r[i] = saved_state->r[i];
			machine_thread_get_state_kprintf("machine_thread_get_state: pc 0x%x r0 0x%x sp  0x%x\n",
					 state->pc, state->r[0], state->sp);

			if (*count != ARM_UNIFIED_THREAD_STATE_COUNT) {
				*count = ARM_THREAD_STATE_COUNT;
			}
			break;
		}
	case ARM_EXCEPTION_STATE:{
			struct arm_exception_state *state;
			struct arm_saved_state *saved_state;

			if (*count < ARM_EXCEPTION_STATE_COUNT)
				return (KERN_INVALID_ARGUMENT);

			state = (struct arm_exception_state *) tstate;
			saved_state = &thread->machine.PcbData;

			state->exception = saved_state->exception;
			state->fsr = saved_state->fsr;
			state->far = saved_state->far;

			*count = ARM_EXCEPTION_STATE_COUNT;
			break;
		}
	case ARM_VFP_STATE:{
#if	__ARM_VFP__
			struct arm_vfp_state *state;
			struct arm_vfpsaved_state *saved_state;
			unsigned int    i;
			unsigned int	max;

			if (*count < ARM_VFP_STATE_COUNT) {
				if (*count < ARM_VFPV2_STATE_COUNT)
					return (KERN_INVALID_ARGUMENT);
				else
					*count =  ARM_VFPV2_STATE_COUNT;
			}

			if (*count ==  ARM_VFPV2_STATE_COUNT)
				max = 32;
			else
				max = 64;

			state = (struct arm_vfp_state *) tstate;
			saved_state = find_user_vfp(thread);

			state->fpscr = saved_state->fpscr;
			for (i = 0; i < max; i++)
				state->r[i] = saved_state->r[i];

#endif
			break;
		}
	case ARM_DEBUG_STATE:{
			arm_debug_state_t *state;
			arm_debug_state_t *thread_state;

                        if (*count < ARM_DEBUG_STATE_COUNT)
				return (KERN_INVALID_ARGUMENT);
			
                        state = (arm_debug_state_t *) tstate;
                        thread_state = find_debug_state(thread);
                        
                        if (thread_state == NULL)
				bzero(state, sizeof(arm_debug_state_t));
                        else
				bcopy(thread_state, state, sizeof(arm_debug_state_t));
			
                        *count = ARM_DEBUG_STATE_COUNT;
                        break;
		}

	default:
		return (KERN_INVALID_ARGUMENT);
	}
	return (KERN_SUCCESS);
}