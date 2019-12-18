#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netlink_skb_parms {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * key; } ;
struct hv_kvp_msg_enumerate {TYPE_1__ data; } ;
struct TYPE_4__ {struct hv_kvp_msg_enumerate kvp_enum_data; } ;
struct hv_kvp_msg {int error; TYPE_2__ body; } ;
struct cn_msg {scalar_t__ data; } ;

/* Variables and functions */
 int HV_S_CONT ; 
#define  KVP_OP_REGISTER 129 
#define  KVP_OP_REGISTER1 128 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int dm_reg_value ; 
 int in_hand_shake ; 
 scalar_t__ kvp_handle_handshake (struct hv_kvp_msg*) ; 
 int /*<<< orphan*/  kvp_respond_to_host (struct hv_kvp_msg*,int) ; 
 int /*<<< orphan*/  kvp_work ; 

__attribute__((used)) static void
kvp_cn_callback(struct cn_msg *msg, struct netlink_skb_parms *nsp)
{
	struct hv_kvp_msg *message;
	struct hv_kvp_msg_enumerate *data;
	int	error = 0;

	message = (struct hv_kvp_msg *)msg->data;

	/*
	 * If we are negotiating the version information
	 * with the daemon; handle that first.
	 */

	if (in_hand_shake) {
		if (kvp_handle_handshake(message))
			in_hand_shake = false;
		return;
	}

	/*
	 * Based on the version of the daemon, we propagate errors from the
	 * daemon differently.
	 */

	data = &message->body.kvp_enum_data;

	switch (dm_reg_value) {
	case KVP_OP_REGISTER:
		/*
		 * Null string is used to pass back error condition.
		 */
		if (data->data.key[0] == 0)
			error = HV_S_CONT;
		break;

	case KVP_OP_REGISTER1:
		/*
		 * We use the message header information from
		 * the user level daemon to transmit errors.
		 */
		error = message->error;
		break;
	}

	/*
	 * Complete the transaction by forwarding the key value
	 * to the host. But first, cancel the timeout.
	 */
	if (cancel_delayed_work_sync(&kvp_work))
		kvp_respond_to_host(message, error);
}