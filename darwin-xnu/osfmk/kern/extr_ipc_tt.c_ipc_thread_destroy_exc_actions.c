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
typedef  TYPE_1__* thread_t ;
struct exception_action {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * exc_actions; } ;

/* Variables and functions */
 size_t EXC_TYPES_COUNT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mac_exc_free_action_label (int /*<<< orphan*/ *) ; 

void
ipc_thread_destroy_exc_actions(
	thread_t	thread)
{
	if (thread->exc_actions != NULL) {
#if CONFIG_MACF
		for (size_t i = 0; i < EXC_TYPES_COUNT; ++i) {
			mac_exc_free_action_label(thread->exc_actions + i);
		}
#endif

		kfree(thread->exc_actions, 
		      sizeof(struct exception_action) * EXC_TYPES_COUNT);
		thread->exc_actions = NULL;
	}
}