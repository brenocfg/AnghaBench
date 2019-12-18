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

/* Variables and functions */
 int bus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_acpi_dev ; 
 int /*<<< orphan*/  hv_bus ; 
 int /*<<< orphan*/  hv_cleanup () ; 
 int hv_init () ; 
 int /*<<< orphan*/  hv_register_vmbus_handler (int,int /*<<< orphan*/ ) ; 
 int hv_synic_alloc () ; 
 int /*<<< orphan*/  hv_synic_free () ; 
 int /*<<< orphan*/  hv_synic_init ; 
 int /*<<< orphan*/  msg_dpc ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_handler (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmbus_connect () ; 
 int /*<<< orphan*/  vmbus_flow_handler ; 
 int /*<<< orphan*/  vmbus_isr ; 
 int /*<<< orphan*/  vmbus_on_msg_dpc ; 
 int /*<<< orphan*/  vmbus_request_offers () ; 

__attribute__((used)) static int vmbus_bus_init(int irq)
{
	int ret;

	/* Hypervisor initialization...setup hypercall page..etc */
	ret = hv_init();
	if (ret != 0) {
		pr_err("Unable to initialize the hypervisor - 0x%x\n", ret);
		return ret;
	}

	tasklet_init(&msg_dpc, vmbus_on_msg_dpc, 0);

	ret = bus_register(&hv_bus);
	if (ret)
		goto err_cleanup;

	ret = request_irq(irq, vmbus_isr, 0, driver_name, hv_acpi_dev);

	if (ret != 0) {
		pr_err("Unable to request IRQ %d\n",
			   irq);
		goto err_unregister;
	}

	/*
	 * Vmbus interrupts can be handled concurrently on
	 * different CPUs. Establish an appropriate interrupt flow
	 * handler that can support this model.
	 */
	set_irq_handler(irq, vmbus_flow_handler);

	/*
	 * Register our interrupt handler.
	 */
	hv_register_vmbus_handler(irq, vmbus_isr);

	ret = hv_synic_alloc();
	if (ret)
		goto err_alloc;
	/*
	 * Initialize the per-cpu interrupt state and
	 * connect to the host.
	 */
	on_each_cpu(hv_synic_init, NULL, 1);
	ret = vmbus_connect();
	if (ret)
		goto err_alloc;

	vmbus_request_offers();

	return 0;

err_alloc:
	hv_synic_free();
	free_irq(irq, hv_acpi_dev);

err_unregister:
	bus_unregister(&hv_bus);

err_cleanup:
	hv_cleanup();

	return ret;
}