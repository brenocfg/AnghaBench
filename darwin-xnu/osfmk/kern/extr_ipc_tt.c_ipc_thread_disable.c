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
typedef  scalar_t__ ipc_port_t ;
struct TYPE_3__ {scalar_t__ ith_self; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_NONE ; 
 int /*<<< orphan*/  IKO_NULL ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_thread_disable(
	thread_t	thread)
{
	ipc_port_t	kport = thread->ith_self;

	if (kport != IP_NULL)
		ipc_kobject_set(kport, IKO_NULL, IKOT_NONE);
}