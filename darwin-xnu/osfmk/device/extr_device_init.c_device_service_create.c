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
typedef  int /*<<< orphan*/  ipc_kobject_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_IO_MASTER_PORT ; 
 int /*<<< orphan*/  IKOT_MASTER_DEVICE ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  datadev_init () ; 
 int /*<<< orphan*/  dev_lck_attr ; 
 int /*<<< orphan*/  dev_lck_grp ; 
 int /*<<< orphan*/  dev_lck_grp_attr ; 
 int /*<<< orphan*/  device_pager_init () ; 
 int /*<<< orphan*/  ds_init () ; 
 int /*<<< orphan*/  host_priv_self () ; 
 int /*<<< orphan*/  io_done_thread ; 
 int /*<<< orphan*/  iokit_obj_to_port_binding_lock ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 int /*<<< orphan*/  ipc_port_make_send (scalar_t__) ; 
 int /*<<< orphan*/  kernel_set_special_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_task ; 
 int /*<<< orphan*/  kernel_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_device_kobject ; 
 scalar_t__ master_device_port ; 
 int /*<<< orphan*/  net_io_init () ; 
 int /*<<< orphan*/  net_thread ; 
 int /*<<< orphan*/  panic (char*) ; 

void
device_service_create(void)
{
	master_device_port = ipc_port_alloc_kernel();
	if (master_device_port == IP_NULL)
	    panic("can't allocate master device port");

	ipc_kobject_set(master_device_port, (ipc_kobject_t)&master_device_kobject, IKOT_MASTER_DEVICE);
	kernel_set_special_port(host_priv_self(), HOST_IO_MASTER_PORT,
				ipc_port_make_send(master_device_port));

	/* allocate device lock group attribute and group */
	dev_lck_grp_attr= lck_grp_attr_alloc_init();
	dev_lck_grp = lck_grp_alloc_init("device",  dev_lck_grp_attr);

	/* Allocate device lock attribute */
	dev_lck_attr = lck_attr_alloc_init();

	/* Initialize the IOKit object to port binding lock */
	lck_mtx_init(&iokit_obj_to_port_binding_lock, dev_lck_grp, dev_lck_attr);

#if 0
	ds_init();
	net_io_init();
	device_pager_init();
	datadev_init();

	(void) kernel_thread(kernel_task, io_done_thread, (char *)0);
	(void) kernel_thread(kernel_task, net_thread, (char *)0);
#endif
}