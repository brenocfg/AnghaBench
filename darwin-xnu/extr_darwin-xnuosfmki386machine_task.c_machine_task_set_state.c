#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ds64; int /*<<< orphan*/  ds32; } ;
struct TYPE_7__ {int const flavor; int /*<<< orphan*/  count; } ;
struct TYPE_9__ {TYPE_2__ uds; TYPE_1__ dsh; } ;
typedef  TYPE_3__ x86_debug_state_t ;
typedef  int /*<<< orphan*/  x86_debug_state64_t ;
typedef  int /*<<< orphan*/  x86_debug_state32_t ;
typedef  scalar_t__ thread_state_t ;
typedef  TYPE_4__* task_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_10__ {int /*<<< orphan*/ * task_debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  copy_debug_state32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_debug_state64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_state_is_valid32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_state_is_valid64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ids_zone ; 
 int /*<<< orphan*/  task_has_64Bit_addr (TYPE_4__*) ; 
#define  x86_DEBUG_STATE 130 
#define  x86_DEBUG_STATE32 129 
 int /*<<< orphan*/  x86_DEBUG_STATE32_COUNT ; 
#define  x86_DEBUG_STATE64 128 
 int /*<<< orphan*/  x86_DEBUG_STATE64_COUNT ; 
 int /*<<< orphan*/  x86_DEBUG_STATE_COUNT ; 
 void* zalloc (int /*<<< orphan*/ ) ; 

kern_return_t
machine_task_set_state(
		task_t task, 
		int flavor,
		thread_state_t state, 
		mach_msg_type_number_t state_count)
{
	switch (flavor) {
		case x86_DEBUG_STATE32:
		{
			x86_debug_state32_t *tstate = (x86_debug_state32_t*) state;
			if ((task_has_64Bit_addr(task)) ||
					(state_count != x86_DEBUG_STATE32_COUNT) || 
					(!debug_state_is_valid32(tstate))) {
				return KERN_INVALID_ARGUMENT;
			}

			if (task->task_debug == NULL) {
				task->task_debug = zalloc(ids_zone);
			}

			copy_debug_state32(tstate, (x86_debug_state32_t*) task->task_debug, FALSE);
			
			return KERN_SUCCESS;
		}
		case x86_DEBUG_STATE64:
		{
			x86_debug_state64_t *tstate = (x86_debug_state64_t*) state;

			if ((!task_has_64Bit_addr(task)) ||
					(state_count != x86_DEBUG_STATE64_COUNT) || 
					(!debug_state_is_valid64(tstate))) {
				return KERN_INVALID_ARGUMENT;
			}

			if (task->task_debug == NULL) {
				task->task_debug = zalloc(ids_zone);
			}
			
			copy_debug_state64(tstate, (x86_debug_state64_t*) task->task_debug, FALSE);
			
			return KERN_SUCCESS;		
		}
		case x86_DEBUG_STATE:
		{
			x86_debug_state_t *tstate = (x86_debug_state_t*) state;

			if (state_count != x86_DEBUG_STATE_COUNT) {
				return KERN_INVALID_ARGUMENT;
			}

			if ((tstate->dsh.flavor == x86_DEBUG_STATE32) && 
					(tstate->dsh.count == x86_DEBUG_STATE32_COUNT) &&
					(!task_has_64Bit_addr(task)) &&
					debug_state_is_valid32(&tstate->uds.ds32)) {
				
				if (task->task_debug == NULL) {
					task->task_debug = zalloc(ids_zone);
				}

				copy_debug_state32(&tstate->uds.ds32, (x86_debug_state32_t*) task->task_debug, FALSE);
				return KERN_SUCCESS;

			} else if ((tstate->dsh.flavor == x86_DEBUG_STATE64) && 
					(tstate->dsh.count == x86_DEBUG_STATE64_COUNT) &&
					task_has_64Bit_addr(task) &&
					debug_state_is_valid64(&tstate->uds.ds64)) {
				
				if (task->task_debug == NULL) {
					task->task_debug = zalloc(ids_zone);
				}

				copy_debug_state64(&tstate->uds.ds64, (x86_debug_state64_t*) task->task_debug, FALSE);
				return KERN_SUCCESS;
			} else {
				return KERN_INVALID_ARGUMENT;
			}
		}
		default:
		{
			return KERN_INVALID_ARGUMENT;
		}
	}
}