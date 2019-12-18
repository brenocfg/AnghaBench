#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct acpi_ipmi_device {int /*<<< orphan*/  head; int /*<<< orphan*/  tx_msg_list; int /*<<< orphan*/  tx_msg_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipmi_devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__ driver_data ; 
 int /*<<< orphan*/  ipmi_install_space_handler (struct acpi_ipmi_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_add_ipmi_device(struct acpi_ipmi_device *ipmi_device)
{

	INIT_LIST_HEAD(&ipmi_device->head);

	mutex_init(&ipmi_device->tx_msg_lock);
	INIT_LIST_HEAD(&ipmi_device->tx_msg_list);
	ipmi_install_space_handler(ipmi_device);

	list_add_tail(&ipmi_device->head, &driver_data.ipmi_devices);
}