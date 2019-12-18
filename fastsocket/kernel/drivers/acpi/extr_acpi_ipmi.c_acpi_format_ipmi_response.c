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
struct acpi_ipmi_msg {int /*<<< orphan*/  rx_len; int /*<<< orphan*/  rx_data; int /*<<< orphan*/  msg_done; } ;
struct acpi_ipmi_buffer {int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_IPMI_OK ; 
 int /*<<< orphan*/  ACPI_IPMI_TIMEOUT ; 
 int /*<<< orphan*/  ACPI_IPMI_UNKNOWN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_format_ipmi_response(struct acpi_ipmi_msg *msg,
		acpi_integer *value, int rem_time)
{
	struct acpi_ipmi_buffer *buffer;

	/*
	 * value is also used as output parameter. It represents the response
	 * IPMI message returned by IPMI command.
	 */
	buffer = (struct acpi_ipmi_buffer *)value;
	if (!rem_time && !msg->msg_done) {
		buffer->status = ACPI_IPMI_TIMEOUT;
		return;
	}
	/*
	 * If the flag of msg_done is not set or the recv length is zero, it
	 * means that the IPMI command is not executed correctly.
	 * The status code will be ACPI_IPMI_UNKNOWN.
	 */
	if (!msg->msg_done || !msg->rx_len) {
		buffer->status = ACPI_IPMI_UNKNOWN;
		return;
	}
	/*
	 * If the IPMI response message is obtained correctly, the status code
	 * will be ACPI_IPMI_OK
	 */
	buffer->status = ACPI_IPMI_OK;
	buffer->length = msg->rx_len;
	memcpy(buffer->data, msg->rx_data, msg->rx_len);
}