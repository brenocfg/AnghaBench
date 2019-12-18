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
typedef  int thread_destruct_special_reply_port_rights_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
#define  THREAD_SPECIAL_REPLY_PORT_ALL 130 
#define  THREAD_SPECIAL_REPLY_PORT_RECEIVE_ONLY 129 
#define  THREAD_SPECIAL_REPLY_PORT_SEND_ONLY 128 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_port_destruct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 

kern_return_t
thread_destruct_special_reply_port(
		mach_port_name_t port,
		thread_destruct_special_reply_port_rights_t rights)
{
	switch (rights) {
	case THREAD_SPECIAL_REPLY_PORT_ALL:
		return mach_port_destruct(mach_task_self(), port, -1, 0);

	case THREAD_SPECIAL_REPLY_PORT_RECEIVE_ONLY:
		return mach_port_destruct(mach_task_self(), port, 0, 0);

	case THREAD_SPECIAL_REPLY_PORT_SEND_ONLY:
		return mach_port_deallocate(mach_task_self(), port);

	default:
		return KERN_INVALID_ARGUMENT;
	}
}