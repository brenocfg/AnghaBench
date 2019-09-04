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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_state_t ;
struct x86_act_context64 {int /*<<< orphan*/  fs; int /*<<< orphan*/  ss; } ;
struct x86_act_context32 {int /*<<< orphan*/  fs; int /*<<< orphan*/  ss; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  kfree (struct x86_act_context64*,int) ; 
 scalar_t__ machine_thread_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_is_64bit_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_FLOAT_STATE32 ; 
 int /*<<< orphan*/  x86_FLOAT_STATE32_COUNT ; 
 int /*<<< orphan*/  x86_FLOAT_STATE64 ; 
 int /*<<< orphan*/  x86_FLOAT_STATE64_COUNT ; 
 int /*<<< orphan*/  x86_SAVED_STATE32 ; 
 int /*<<< orphan*/  x86_SAVED_STATE32_COUNT ; 
 int /*<<< orphan*/  x86_SAVED_STATE64 ; 
 int /*<<< orphan*/  x86_SAVED_STATE64_COUNT ; 

void 
act_thread_catt(void *ctx)
{
        thread_t thr_act = current_thread();
	kern_return_t kret;

	if (ctx == (void *)NULL)
				return;

        if (thread_is_64bit_addr(thr_act)) {
	        struct x86_act_context64 *ic64;

	        ic64 = (struct x86_act_context64 *)ctx;

		kret = machine_thread_set_state(thr_act, x86_SAVED_STATE64,
						(thread_state_t) &ic64->ss, x86_SAVED_STATE64_COUNT);
		if (kret == KERN_SUCCESS) {
			        machine_thread_set_state(thr_act, x86_FLOAT_STATE64,
							 (thread_state_t) &ic64->fs, x86_FLOAT_STATE64_COUNT);
		}
		kfree(ic64, sizeof(struct x86_act_context64));
	} else {
	        struct x86_act_context32 *ic32;

	        ic32 = (struct x86_act_context32 *)ctx;

		kret = machine_thread_set_state(thr_act, x86_SAVED_STATE32,
						(thread_state_t) &ic32->ss, x86_SAVED_STATE32_COUNT);
		if (kret == KERN_SUCCESS) {
			(void) machine_thread_set_state(thr_act, x86_FLOAT_STATE32,
						 (thread_state_t) &ic32->fs, x86_FLOAT_STATE32_COUNT);
		}
		kfree(ic32, sizeof(struct x86_act_context32));
	}
}