#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_2__* thread_t ;
typedef  int* thread_state_t ;
typedef  int thread_flavor_t ;
struct arm_vfp_state {int dummy; } ;
struct arm_saved_state64 {int /*<<< orphan*/  esr; int /*<<< orphan*/  far; int /*<<< orphan*/  exception; } ;
struct arm_saved_state32 {int /*<<< orphan*/  far; int /*<<< orphan*/  esr; int /*<<< orphan*/  exception; } ;
struct arm_exception_state64 {int /*<<< orphan*/  esr; int /*<<< orphan*/  far; int /*<<< orphan*/  exception; } ;
struct arm_exception_state {int /*<<< orphan*/  far; int /*<<< orphan*/  fsr; int /*<<< orphan*/  exception; } ;
typedef  int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  struct arm_vfp_state arm_neon_state_t ;
typedef  struct arm_vfp_state arm_neon_state64_t ;
typedef  struct arm_vfp_state arm_neon_saved_state64_t ;
typedef  struct arm_vfp_state arm_neon_saved_state32_t ;
typedef  struct arm_vfp_state arm_legacy_debug_state_t ;
typedef  struct arm_vfp_state arm_debug_state64_t ;
typedef  struct arm_vfp_state arm_debug_state32_t ;
struct TYPE_7__ {int /*<<< orphan*/  uNeon; int /*<<< orphan*/  upcb; } ;
struct TYPE_8__ {TYPE_1__ machine; } ;

/* Variables and functions */
#define  ARM_DEBUG_STATE 140 
#define  ARM_DEBUG_STATE32 139 
 int ARM_DEBUG_STATE32_COUNT ; 
#define  ARM_DEBUG_STATE64 138 
 int ARM_DEBUG_STATE64_COUNT ; 
#define  ARM_EXCEPTION_STATE 137 
#define  ARM_EXCEPTION_STATE64 136 
 int ARM_EXCEPTION_STATE64_COUNT ; 
 int ARM_EXCEPTION_STATE_COUNT ; 
 int ARM_LEGACY_DEBUG_STATE_COUNT ; 
#define  ARM_NEON_STATE 135 
#define  ARM_NEON_STATE64 134 
 int ARM_NEON_STATE64_COUNT ; 
 int ARM_NEON_STATE_COUNT ; 
#define  ARM_THREAD_STATE 133 
#define  ARM_THREAD_STATE32 132 
#define  ARM_THREAD_STATE64 131 
 int ARM_VFPV2_STATE_COUNT ; 
#define  ARM_VFP_STATE 130 
 int ARM_VFP_STATE_COUNT ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  THREAD_STATE_FLAVOR_LIST 129 
#define  THREAD_STATE_FLAVOR_LIST_NEW 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (struct arm_vfp_state*,struct arm_vfp_state*,int) ; 
 int /*<<< orphan*/  bzero (struct arm_vfp_state*,int) ; 
 struct arm_vfp_state* find_debug_state32 (TYPE_2__*) ; 
 struct arm_vfp_state* find_debug_state64 (TYPE_2__*) ; 
 int /*<<< orphan*/  handle_get_arm32_thread_state (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_get_arm64_thread_state (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_get_arm_thread_state (int*,int*,int /*<<< orphan*/ ) ; 
 struct arm_vfp_state* neon_state32 (int /*<<< orphan*/ ) ; 
 struct arm_vfp_state* neon_state64 (int /*<<< orphan*/ ) ; 
 struct arm_saved_state32* saved_state32 (int /*<<< orphan*/ ) ; 
 struct arm_saved_state64* saved_state64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_is_64bit_data (TYPE_2__*) ; 

kern_return_t
machine_thread_get_state(
			 thread_t thread,
			 thread_flavor_t flavor,
			 thread_state_t tstate,
			 mach_msg_type_number_t * count)
{
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

	case THREAD_STATE_FLAVOR_LIST_NEW:
		if (*count < 4)
			return (KERN_INVALID_ARGUMENT);

		tstate[0] = ARM_THREAD_STATE;
		tstate[1] = ARM_VFP_STATE;
		tstate[2] = thread_is_64bit_data(thread) ? ARM_EXCEPTION_STATE64 : ARM_EXCEPTION_STATE;
		tstate[3] = thread_is_64bit_data(thread) ? ARM_DEBUG_STATE64 : ARM_DEBUG_STATE32;
		*count = 4;
		break;

	case ARM_THREAD_STATE:
	{
		kern_return_t rn = handle_get_arm_thread_state(tstate, count, thread->machine.upcb);
		if (rn) return rn;
		break;
	}
	case ARM_THREAD_STATE32:
	{
		if (thread_is_64bit_data(thread))
			return KERN_INVALID_ARGUMENT;

		kern_return_t rn = handle_get_arm32_thread_state(tstate, count, thread->machine.upcb);
		if (rn) return rn;
		break;
	}
#if __arm64__
	case ARM_THREAD_STATE64:
	{
		if (!thread_is_64bit_data(thread))
			return KERN_INVALID_ARGUMENT;

		kern_return_t rn = handle_get_arm64_thread_state(tstate, count, thread->machine.upcb);
		if (rn) return rn;
		break;
	}
#endif
	case ARM_EXCEPTION_STATE:{
			struct arm_exception_state *state;
			struct arm_saved_state32 *saved_state;

			if (*count < ARM_EXCEPTION_STATE_COUNT)
				return (KERN_INVALID_ARGUMENT);
			if (thread_is_64bit_data(thread))
				return (KERN_INVALID_ARGUMENT);

			state = (struct arm_exception_state *) tstate;
			saved_state = saved_state32(thread->machine.upcb);

			state->exception = saved_state->exception;
			state->fsr = saved_state->esr;
			state->far = saved_state->far;

			*count = ARM_EXCEPTION_STATE_COUNT;
			break;
		}
	case ARM_EXCEPTION_STATE64:{
			struct arm_exception_state64 *state;
			struct arm_saved_state64 *saved_state;

			if (*count < ARM_EXCEPTION_STATE64_COUNT)
				return (KERN_INVALID_ARGUMENT);
			if (!thread_is_64bit_data(thread))
				return (KERN_INVALID_ARGUMENT);

			state = (struct arm_exception_state64 *) tstate;
			saved_state = saved_state64(thread->machine.upcb);

			state->exception = saved_state->exception;
			state->far = saved_state->far;
			state->esr = saved_state->esr;

			*count = ARM_EXCEPTION_STATE64_COUNT;
			break;
		}
	case ARM_DEBUG_STATE:{
			arm_legacy_debug_state_t *state;
			arm_debug_state32_t *thread_state;

			if (*count < ARM_LEGACY_DEBUG_STATE_COUNT)
				return (KERN_INVALID_ARGUMENT);
			
			if (thread_is_64bit_data(thread))
				return (KERN_INVALID_ARGUMENT);

			state = (arm_legacy_debug_state_t *) tstate;
			thread_state = find_debug_state32(thread);
                        
			if (thread_state == NULL)
				bzero(state, sizeof(arm_legacy_debug_state_t));
			else
				bcopy(thread_state, state, sizeof(arm_legacy_debug_state_t));
			
			*count = ARM_LEGACY_DEBUG_STATE_COUNT;
			break;
		}
	case ARM_DEBUG_STATE32:{
			arm_debug_state32_t *state;
			arm_debug_state32_t *thread_state;

			if (*count < ARM_DEBUG_STATE32_COUNT)
				return (KERN_INVALID_ARGUMENT);
			
			if (thread_is_64bit_data(thread))
				return (KERN_INVALID_ARGUMENT);

			state = (arm_debug_state32_t *) tstate;
			thread_state = find_debug_state32(thread);
                        
			if (thread_state == NULL)
				bzero(state, sizeof(arm_debug_state32_t));
			else
				bcopy(thread_state, state, sizeof(arm_debug_state32_t));
			
			*count = ARM_DEBUG_STATE32_COUNT;
			break;
		}

	case ARM_DEBUG_STATE64:{
			arm_debug_state64_t *state;
			arm_debug_state64_t *thread_state;

			if (*count < ARM_DEBUG_STATE64_COUNT)
				return (KERN_INVALID_ARGUMENT);
			
			if (!thread_is_64bit_data(thread))
				return (KERN_INVALID_ARGUMENT);

			state = (arm_debug_state64_t *) tstate;
			thread_state = find_debug_state64(thread);
                        
			if (thread_state == NULL)
				bzero(state, sizeof(arm_debug_state64_t));
			else
				bcopy(thread_state, state, sizeof(arm_debug_state64_t));
			
			*count = ARM_DEBUG_STATE64_COUNT;
			break;
		}

	case ARM_VFP_STATE:{
			struct arm_vfp_state *state;
			arm_neon_saved_state32_t *thread_state;
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
			thread_state = neon_state32(thread->machine.uNeon);
			/* ARM64 TODO: set fpsr and fpcr from state->fpscr */

			bcopy(thread_state, state, (max + 1)*sizeof(uint32_t));
			*count = (max + 1);
			break;
		}
	case ARM_NEON_STATE:{
		arm_neon_state_t *state;
		arm_neon_saved_state32_t *thread_state;

		if (*count < ARM_NEON_STATE_COUNT)
			return (KERN_INVALID_ARGUMENT);

		if (thread_is_64bit_data(thread))
			return (KERN_INVALID_ARGUMENT);

		state = (arm_neon_state_t *)tstate;
		thread_state = neon_state32(thread->machine.uNeon);

		assert(sizeof(*thread_state) == sizeof(*state));
		bcopy(thread_state, state, sizeof(arm_neon_state_t));

		*count = ARM_NEON_STATE_COUNT;
		break;
		
		}

	case ARM_NEON_STATE64:{
		arm_neon_state64_t *state;
		arm_neon_saved_state64_t *thread_state;

		if (*count < ARM_NEON_STATE64_COUNT)
			return (KERN_INVALID_ARGUMENT);

		if (!thread_is_64bit_data(thread))
			return (KERN_INVALID_ARGUMENT);

		state = (arm_neon_state64_t *)tstate;
		thread_state = neon_state64(thread->machine.uNeon);

		/* For now, these are identical */
		assert(sizeof(*state) == sizeof(*thread_state));
		bcopy(thread_state, state, sizeof(arm_neon_state64_t));

		*count = ARM_NEON_STATE64_COUNT;
		break;
		
		}

	default:
		return (KERN_INVALID_ARGUMENT);
	}
	return (KERN_SUCCESS);
}