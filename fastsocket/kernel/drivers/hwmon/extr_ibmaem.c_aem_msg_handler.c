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
struct TYPE_2__ {int data_len; int /*<<< orphan*/ * data; } ;
struct ipmi_recv_msg {scalar_t__ msgid; TYPE_1__ msg; int /*<<< orphan*/  recv_type; } ;
struct aem_ipmi_data {scalar_t__ tx_msgid; unsigned short rx_msg_len; int /*<<< orphan*/  read_complete; int /*<<< orphan*/  rx_msg_data; int /*<<< orphan*/  rx_result; int /*<<< orphan*/  rx_recv_type; int /*<<< orphan*/  bmc_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_UNKNOWN_ERR_COMPLETION_CODE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ipmi_free_recv_msg (struct ipmi_recv_msg*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 

__attribute__((used)) static void aem_msg_handler(struct ipmi_recv_msg *msg, void *user_msg_data)
{
	unsigned short rx_len;
	struct aem_ipmi_data *data = user_msg_data;

	if (msg->msgid != data->tx_msgid) {
		dev_err(data->bmc_device, "Mismatch between received msgid "
			"(%02x) and transmitted msgid (%02x)!\n",
			(int)msg->msgid,
			(int)data->tx_msgid);
		ipmi_free_recv_msg(msg);
		return;
	}

	data->rx_recv_type = msg->recv_type;
	if (msg->msg.data_len > 0)
		data->rx_result = msg->msg.data[0];
	else
		data->rx_result = IPMI_UNKNOWN_ERR_COMPLETION_CODE;

	if (msg->msg.data_len > 1) {
		rx_len = msg->msg.data_len - 1;
		if (data->rx_msg_len < rx_len)
			rx_len = data->rx_msg_len;
		data->rx_msg_len = rx_len;
		memcpy(data->rx_msg_data, msg->msg.data + 1, data->rx_msg_len);
	} else
		data->rx_msg_len = 0;

	ipmi_free_recv_msg(msg);
	complete(&data->read_complete);
}