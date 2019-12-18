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
struct ipmi_system_interface_addr {int lun; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_smi_msg {int rsp_size; int* rsp; } ;
struct TYPE_3__ {int netfn; int cmd; int data_len; int /*<<< orphan*/  data; } ;
struct ipmi_recv_msg {int /*<<< orphan*/  msg_data; TYPE_1__ msg; int /*<<< orphan*/  recv_type; int /*<<< orphan*/ * user_msg_data; TYPE_2__* user; int /*<<< orphan*/  addr; } ;
struct cmd_rcvr {TYPE_2__* user; } ;
typedef  TYPE_2__* ipmi_user_t ;
typedef  int /*<<< orphan*/  ipmi_smi_t ;
struct TYPE_4__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_OEM_RECV_TYPE ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  deliver_response (struct ipmi_recv_msg*) ; 
 struct cmd_rcvr* find_cmd_rcvr (int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  free_user ; 
 int /*<<< orphan*/  handled_commands ; 
 int /*<<< orphan*/  invalid_commands ; 
 struct ipmi_recv_msg* ipmi_alloc_recv_msg () ; 
 int /*<<< orphan*/  ipmi_inc_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  unhandled_commands ; 

__attribute__((used)) static int handle_oem_get_msg_cmd(ipmi_smi_t          intf,
				  struct ipmi_smi_msg *msg)
{
	struct cmd_rcvr       *rcvr;
	int                   rv = 0;
	unsigned char         netfn;
	unsigned char         cmd;
	unsigned char         chan;
	ipmi_user_t           user = NULL;
	struct ipmi_system_interface_addr *smi_addr;
	struct ipmi_recv_msg  *recv_msg;

	/*
	 * We expect the OEM SW to perform error checking
	 * so we just do some basic sanity checks
	 */
	if (msg->rsp_size < 4) {
		/* Message not big enough, just ignore it. */
		ipmi_inc_stat(intf, invalid_commands);
		return 0;
	}

	if (msg->rsp[2] != 0) {
		/* An error getting the response, just ignore it. */
		return 0;
	}

	/*
	 * This is an OEM Message so the OEM needs to know how
	 * handle the message. We do no interpretation.
	 */
	netfn = msg->rsp[0] >> 2;
	cmd = msg->rsp[1];
	chan = msg->rsp[3] & 0xf;

	rcu_read_lock();
	rcvr = find_cmd_rcvr(intf, netfn, cmd, chan);
	if (rcvr) {
		user = rcvr->user;
		kref_get(&user->refcount);
	} else
		user = NULL;
	rcu_read_unlock();

	if (user == NULL) {
		/* We didn't find a user, just give up. */
		ipmi_inc_stat(intf, unhandled_commands);

		/*
		 * Don't do anything with these messages, just allow
		 * them to be freed.
		 */

		rv = 0;
	} else {
		/* Deliver the message to the user. */
		ipmi_inc_stat(intf, handled_commands);

		recv_msg = ipmi_alloc_recv_msg();
		if (!recv_msg) {
			/*
			 * We couldn't allocate memory for the
			 * message, so requeue it for handling
			 * later.
			 */
			rv = 1;
			kref_put(&user->refcount, free_user);
		} else {
			/*
			 * OEM Messages are expected to be delivered via
			 * the system interface to SMS software.  We might
			 * need to visit this again depending on OEM
			 * requirements
			 */
			smi_addr = ((struct ipmi_system_interface_addr *)
				    &(recv_msg->addr));
			smi_addr->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
			smi_addr->channel = IPMI_BMC_CHANNEL;
			smi_addr->lun = msg->rsp[0] & 3;

			recv_msg->user = user;
			recv_msg->user_msg_data = NULL;
			recv_msg->recv_type = IPMI_OEM_RECV_TYPE;
			recv_msg->msg.netfn = msg->rsp[0] >> 2;
			recv_msg->msg.cmd = msg->rsp[1];
			recv_msg->msg.data = recv_msg->msg_data;

			/*
			 * The message starts at byte 4 which follows the
			 * the Channel Byte in the "GET MESSAGE" command
			 */
			recv_msg->msg.data_len = msg->rsp_size - 4;
			memcpy(recv_msg->msg_data,
			       &(msg->rsp[4]),
			       msg->rsp_size - 4);
			deliver_response(recv_msg);
		}
	}

	return rv;
}