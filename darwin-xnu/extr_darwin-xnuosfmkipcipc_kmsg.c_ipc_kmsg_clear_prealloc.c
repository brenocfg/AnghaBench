#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_port_t ;
typedef  TYPE_2__* ipc_kmsg_t ;
struct TYPE_9__ {int /*<<< orphan*/  ikm_turnstile; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CLEAR_PREALLOC (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imq_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_port_send_turnstile (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
ipc_kmsg_clear_prealloc(
	ipc_kmsg_t		kmsg,
	ipc_port_t		port)
{
	/* take the mqueue lock since the turnstile is protected under it */
	imq_lock(&port->ip_messages);

	IP_CLEAR_PREALLOC(port, kmsg);
	set_port_send_turnstile(port, kmsg->ikm_turnstile);
	imq_unlock(&port->ip_messages);
}