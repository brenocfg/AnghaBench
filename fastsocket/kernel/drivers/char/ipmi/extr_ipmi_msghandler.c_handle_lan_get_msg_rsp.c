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
struct ipmi_smi_msg {int rsp_size; int* rsp; } ;
struct TYPE_2__ {int netfn; int data_len; int /*<<< orphan*/  data; } ;
struct ipmi_recv_msg {int /*<<< orphan*/  recv_type; TYPE_1__ msg; int /*<<< orphan*/  msg_data; } ;
struct ipmi_lan_addr {int session_handle; int remote_SWID; int local_SWID; int channel; int privilege; int lun; int /*<<< orphan*/  addr_type; } ;
struct ipmi_addr {int dummy; } ;
typedef  int /*<<< orphan*/  ipmi_smi_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_LAN_ADDR_TYPE ; 
 int /*<<< orphan*/  IPMI_RESPONSE_RECV_TYPE ; 
 int /*<<< orphan*/  deliver_response (struct ipmi_recv_msg*) ; 
 int /*<<< orphan*/  handled_lan_responses ; 
 scalar_t__ intf_find_seq (int /*<<< orphan*/ ,int,int,int,int,struct ipmi_addr*,struct ipmi_recv_msg**) ; 
 int /*<<< orphan*/  invalid_lan_responses ; 
 int /*<<< orphan*/  ipmi_inc_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  unhandled_lan_responses ; 

__attribute__((used)) static int handle_lan_get_msg_rsp(ipmi_smi_t          intf,
				  struct ipmi_smi_msg *msg)
{
	struct ipmi_lan_addr  lan_addr;
	struct ipmi_recv_msg  *recv_msg;


	/*
	 * This is 13, not 12, because the response must contain a
	 * completion code.
	 */
	if (msg->rsp_size < 13) {
		/* Message not big enough, just ignore it. */
		ipmi_inc_stat(intf, invalid_lan_responses);
		return 0;
	}

	if (msg->rsp[2] != 0) {
		/* An error getting the response, just ignore it. */
		return 0;
	}

	lan_addr.addr_type = IPMI_LAN_ADDR_TYPE;
	lan_addr.session_handle = msg->rsp[4];
	lan_addr.remote_SWID = msg->rsp[8];
	lan_addr.local_SWID = msg->rsp[5];
	lan_addr.channel = msg->rsp[3] & 0x0f;
	lan_addr.privilege = msg->rsp[3] >> 4;
	lan_addr.lun = msg->rsp[9] & 3;

	/*
	 * It's a response from a remote entity.  Look up the sequence
	 * number and handle the response.
	 */
	if (intf_find_seq(intf,
			  msg->rsp[9] >> 2,
			  msg->rsp[3] & 0x0f,
			  msg->rsp[10],
			  (msg->rsp[6] >> 2) & (~1),
			  (struct ipmi_addr *) &(lan_addr),
			  &recv_msg)) {
		/*
		 * We were unable to find the sequence number,
		 * so just nuke the message.
		 */
		ipmi_inc_stat(intf, unhandled_lan_responses);
		return 0;
	}

	memcpy(recv_msg->msg_data,
	       &(msg->rsp[11]),
	       msg->rsp_size - 11);
	/*
	 * The other fields matched, so no need to set them, except
	 * for netfn, which needs to be the response that was
	 * returned, not the request value.
	 */
	recv_msg->msg.netfn = msg->rsp[6] >> 2;
	recv_msg->msg.data = recv_msg->msg_data;
	recv_msg->msg.data_len = msg->rsp_size - 12;
	recv_msg->recv_type = IPMI_RESPONSE_RECV_TYPE;
	ipmi_inc_stat(intf, handled_lan_responses);
	deliver_response(recv_msg);

	return 0;
}