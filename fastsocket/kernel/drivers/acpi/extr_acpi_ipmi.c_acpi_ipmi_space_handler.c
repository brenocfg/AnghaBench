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
typedef  int u32 ;
struct acpi_ipmi_msg {int /*<<< orphan*/  head; int /*<<< orphan*/  tx_complete; int /*<<< orphan*/  tx_message; int /*<<< orphan*/  tx_msgid; int /*<<< orphan*/  addr; } ;
struct acpi_ipmi_device {int /*<<< orphan*/  tx_msg_lock; int /*<<< orphan*/  user_interface; int /*<<< orphan*/  tx_msg_list; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
typedef  int /*<<< orphan*/  acpi_integer ;

/* Variables and functions */
 int ACPI_IO_MASK ; 
 int ACPI_READ ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  IPMI_TIMEOUT ; 
 struct acpi_ipmi_msg* acpi_alloc_ipmi_msg (struct acpi_ipmi_device*) ; 
 int /*<<< orphan*/  acpi_format_ipmi_msg (struct acpi_ipmi_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_format_ipmi_response (struct acpi_ipmi_msg*,int /*<<< orphan*/ *,int) ; 
 int ipmi_request_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_ipmi_msg*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ipmi_space_handler(u32 function, acpi_physical_address address,
		      u32 bits, acpi_integer *value,
		      void *handler_context, void *region_context)
{
	struct acpi_ipmi_msg *tx_msg;
	struct acpi_ipmi_device *ipmi_device = handler_context;
	int err, rem_time;
	acpi_status status;
	/*
	 * IPMI opregion message.
	 * IPMI message is firstly written to the BMC and system software
	 * can get the respsonse. So it is unmeaningful for the read access
	 * of IPMI opregion.
	 */
	if ((function & ACPI_IO_MASK) == ACPI_READ)
		return AE_TYPE;

	if (!ipmi_device->user_interface)
		return AE_NOT_EXIST;

	tx_msg = acpi_alloc_ipmi_msg(ipmi_device);
	if (!tx_msg)
		return AE_NO_MEMORY;

	acpi_format_ipmi_msg(tx_msg, address, value);
	mutex_lock(&ipmi_device->tx_msg_lock);
	list_add_tail(&tx_msg->head, &ipmi_device->tx_msg_list);
	mutex_unlock(&ipmi_device->tx_msg_lock);
	err = ipmi_request_settime(ipmi_device->user_interface,
					&tx_msg->addr,
					tx_msg->tx_msgid,
					&tx_msg->tx_message,
					NULL, 0, 0, 0);
	if (err) {
		status = AE_ERROR;
		goto end_label;
	}
	rem_time = wait_for_completion_timeout(&tx_msg->tx_complete,
					IPMI_TIMEOUT);
	acpi_format_ipmi_response(tx_msg, value, rem_time);
	status = AE_OK;

end_label:
	mutex_lock(&ipmi_device->tx_msg_lock);
	list_del(&tx_msg->head);
	mutex_unlock(&ipmi_device->tx_msg_lock);
	kfree(tx_msg);
	return status;
}