#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;
struct TYPE_5__ {TYPE_1__* exc_actions; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * label; scalar_t__ port; } ;

/* Variables and functions */
 int EXC_TYPES_COUNT ; 
 int FIRST_EXCEPTION ; 
 int /*<<< orphan*/  HOST_PORT ; 
 int /*<<< orphan*/  HOST_PRIV_PORT ; 
 int /*<<< orphan*/  HOST_SECURITY_PORT ; 
 int /*<<< orphan*/  IKOT_HOST ; 
 int /*<<< orphan*/  IKOT_HOST_PRIV ; 
 int /*<<< orphan*/  IKOT_HOST_SECURITY ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  host_notify_lock_attr ; 
 int /*<<< orphan*/  host_notify_lock_grp ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 int /*<<< orphan*/  ipc_port_make_send (scalar_t__) ; 
 int /*<<< orphan*/  ipc_processor_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_processor_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_pset_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_pset_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_set_special_port (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_processor ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pset0 ; 
 TYPE_2__ realhost ; 

void ipc_host_init(void)
{
	ipc_port_t	port;
	int i;

	lck_mtx_init(&realhost.lock, &host_notify_lock_grp, &host_notify_lock_attr);

	/*
	 *	Allocate and set up the two host ports.
	 */
	port = ipc_port_alloc_kernel();
	if (port == IP_NULL)
		panic("ipc_host_init");

	ipc_kobject_set(port, (ipc_kobject_t) &realhost, IKOT_HOST_SECURITY);
	kernel_set_special_port(&realhost, HOST_SECURITY_PORT,
				ipc_port_make_send(port));

	port = ipc_port_alloc_kernel();
	if (port == IP_NULL)
		panic("ipc_host_init");

	ipc_kobject_set(port, (ipc_kobject_t) &realhost, IKOT_HOST);
	kernel_set_special_port(&realhost, HOST_PORT,
				ipc_port_make_send(port));

	port = ipc_port_alloc_kernel();
	if (port == IP_NULL)
		panic("ipc_host_init");

	ipc_kobject_set(port, (ipc_kobject_t) &realhost, IKOT_HOST_PRIV);
	kernel_set_special_port(&realhost, HOST_PRIV_PORT,
				ipc_port_make_send(port));

	/* the rest of the special ports will be set up later */

	for (i = FIRST_EXCEPTION; i < EXC_TYPES_COUNT; i++) {
			realhost.exc_actions[i].port = IP_NULL;
			/* The mac framework is not yet initialized, so we defer
			 * initializing the labels to later, when they are set
			 * for the first time. */
			realhost.exc_actions[i].label = NULL;
		}/* for */

	/*
	 *	Set up ipc for default processor set.
	 */
	ipc_pset_init(&pset0);
	ipc_pset_enable(&pset0);

	/*
	 *	And for master processor
	 */
	ipc_processor_init(master_processor);
	ipc_processor_enable(master_processor);
}