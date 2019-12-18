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
typedef  int /*<<< orphan*/  ipc_kobject_t ;
struct TYPE_3__ {scalar_t__ ith_rpc_reply; int /*<<< orphan*/  ith_messages; scalar_t__ ith_assertions; int /*<<< orphan*/ * exc_actions; int /*<<< orphan*/ * ith_special_reply_port; int /*<<< orphan*/  ith_sself; scalar_t__ ith_self; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_THREAD ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  ipc_kmsg_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 int /*<<< orphan*/  ipc_port_make_send (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
ipc_thread_init(
	thread_t	thread)
{
	ipc_port_t	kport;

	kport = ipc_port_alloc_kernel();
	if (kport == IP_NULL)
		panic("ipc_thread_init");

	thread->ith_self = kport;
	thread->ith_sself = ipc_port_make_send(kport);
	thread->ith_special_reply_port = NULL;
	thread->exc_actions = NULL;

	ipc_kobject_set(kport, (ipc_kobject_t)thread, IKOT_THREAD);

#if IMPORTANCE_INHERITANCE
	thread->ith_assertions = 0;
#endif

	ipc_kmsg_queue_init(&thread->ith_messages);

	thread->ith_rpc_reply = IP_NULL;
}