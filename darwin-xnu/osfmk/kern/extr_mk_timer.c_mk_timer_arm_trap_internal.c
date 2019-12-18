#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* mk_timer_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_2__* ipc_port_t ;
struct TYPE_7__ {scalar_t__ ip_kobject; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  active; int /*<<< orphan*/  call_entry; int /*<<< orphan*/  is_armed; int /*<<< orphan*/  is_dead; TYPE_2__* port; } ;

/* Variables and functions */
 scalar_t__ IKOT_TIMER ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 int MK_TIMER_CRITICAL ; 
 int /*<<< orphan*/  THREAD_CALL_DELAY_LEEWAY ; 
 int /*<<< orphan*/  THREAD_CALL_DELAY_USER_CRITICAL ; 
 int /*<<< orphan*/  THREAD_CALL_DELAY_USER_NORMAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_space () ; 
 scalar_t__ ip_kotype (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 scalar_t__ ipc_port_translate_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int mach_absolute_time () ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_enter1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_enter_delayed_with_leeway (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
mk_timer_arm_trap_internal(mach_port_name_t name, uint64_t expire_time, uint64_t mk_leeway, uint64_t mk_timer_flags) {
	mk_timer_t			timer;
	ipc_space_t			myspace = current_space();
	ipc_port_t			port;
	kern_return_t			result;

	result = ipc_port_translate_receive(myspace, name, &port);
	if (result != KERN_SUCCESS)
		return (result);

	if (ip_kotype(port) == IKOT_TIMER) {
		timer = (mk_timer_t)port->ip_kobject;
		assert(timer != NULL);

		simple_lock(&timer->lock);
		assert(timer->port == port);
		ip_unlock(port);

		if (!timer->is_dead) {
			timer->is_armed = TRUE;

			if (expire_time > mach_absolute_time()) {
				uint32_t tcflags = THREAD_CALL_DELAY_USER_NORMAL;

				if (mk_timer_flags & MK_TIMER_CRITICAL) {
					tcflags = THREAD_CALL_DELAY_USER_CRITICAL;
				}

				if (mk_leeway != 0) {
					tcflags |= THREAD_CALL_DELAY_LEEWAY;
				}

				if (!thread_call_enter_delayed_with_leeway(
					&timer->call_entry, NULL,
					expire_time, mk_leeway, tcflags)) {

					timer->active++;
				}
			} else {
				if (!thread_call_enter1(&timer->call_entry, NULL))
					timer->active++;
			}
		}

		simple_unlock(&timer->lock);
	} else {
		ip_unlock(port);
		result = KERN_INVALID_ARGUMENT;
	}
	return (result);
}