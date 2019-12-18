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
struct acpi_ipmi_device {int /*<<< orphan*/  head; int /*<<< orphan*/  tx_msg_list; int /*<<< orphan*/ * user_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmi_flush_tx_msg (struct acpi_ipmi_device*) ; 
 int /*<<< orphan*/  ipmi_remove_space_handler (struct acpi_ipmi_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_remove_ipmi_device(struct acpi_ipmi_device *ipmi_device)
{
	/*
	 * If the IPMI user interface is created, it should be
	 * destroyed.
	 */
	if (ipmi_device->user_interface) {
		ipmi_destroy_user(ipmi_device->user_interface);
		ipmi_device->user_interface = NULL;
	}
	/* flush the Tx_msg list */
	if (!list_empty(&ipmi_device->tx_msg_list))
		ipmi_flush_tx_msg(ipmi_device);

	list_del(&ipmi_device->head);
	ipmi_remove_space_handler(ipmi_device);
}