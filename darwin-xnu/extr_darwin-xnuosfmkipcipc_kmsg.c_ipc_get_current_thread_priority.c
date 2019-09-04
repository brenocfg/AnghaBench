#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ thread_qos_t ;
typedef  int /*<<< orphan*/  mach_msg_priority_t ;
struct TYPE_4__ {int /*<<< orphan*/  base_pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  _pthread_priority_make_from_thread_qos (scalar_t__,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ thread_get_requested_qos (TYPE_1__*,int*) ; 
 scalar_t__ thread_user_promotion_qos_for_pri (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mach_msg_priority_t
ipc_get_current_thread_priority(void)
{
	thread_t thread = current_thread();
	thread_qos_t qos;
	int relpri;

	qos = thread_get_requested_qos(thread, &relpri);
	if (!qos) {
		qos = thread_user_promotion_qos_for_pri(thread->base_pri);
		relpri = 0;
	}
	return (mach_msg_priority_t)_pthread_priority_make_from_thread_qos(qos, relpri, 0);
}