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
struct ipmi_smi_msg {int rsp_size; int* rsp; } ;
struct TYPE_3__ {int netfn; int cmd; int data_len; int /*<<< orphan*/  data; } ;
struct ipmi_recv_msg {int msgid; int /*<<< orphan*/  msg_data; TYPE_1__ msg; int /*<<< orphan*/  recv_type; TYPE_2__* user; int /*<<< orphan*/  addr; } ;
struct ipmi_lan_addr {int session_handle; int remote_SWID; int local_SWID; int lun; int channel; int privilege; int /*<<< orphan*/  addr_type; } ;
struct cmd_rcvr {TYPE_2__* user; } ;
typedef  TYPE_2__* ipmi_user_t ;
typedef  int /*<<< orphan*/  ipmi_smi_t ;
struct TYPE_4__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_CMD_RECV_TYPE ; 
 int /*<<< orphan*/  IPMI_LAN_ADDR_TYPE ; 
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

__attribute__((used)) static int handle_lan_get_msg_cmd(ipmi_smi_t          intf,
				  struct ipmi_smi_msg *msg)
{
	struct cmd_rcvr          *rcvr;
	int                      rv = 0;
	unsigned char            netfn;
	unsigned char            cmd;
	unsigned char            chan;
	ipmi_user_t              user = NULL;
	struct ipmi_lan_addr     *lan_addr;
	struct ipmi_recv_msg     *recv_msg;

	if (msg->rsp_size < 12) {
		/* Message not big enough, just ignore it. */
		ipmi_inc_stat(intf, invalid_commands);
		return 0;
	}

	if (msg->rsp[2] != 0) {
		/* An error getting the response, just ignore it. */
		return 0;
	}

	netfn = msg->rsp[6] >> 2;
	cmd = msg->rsp[10];
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
			 * message, so requeue it for handling later.
			 */
			rv = 1;
			kref_put(&user->refcount, free_user);
		} else {
			/* Extract the source address from the data. */
			lan_addr = (struct ipmi_lan_addr *) &recv_msg->addr;
			lan_addr->addr_type = IPMI_LAN_ADDR_TYPE;
			lan_addr->session_handle = msg->rsp[4];
			lan_addr->remote_SWID = msg->rsp[8];
			lan_addr->local_SWID = msg->rsp[5];
			lan_addr->lun = msg->rsp[9] & 3;
			lan_addr->channel = msg->rsp[3] & 0xf;
			lan_addr->privilege = msg->rsp[3] >> 4;

			/*
			 * Extract the rest of the message information
			 * from the IPMB header.
			 */
			recv_msg->user = user;
			recv_msg->recv_type = IPMI_CMD_RECV_TYPE;
			recv_msg->msgid = msg->rsp[9] >> 2;
			recv_msg->msg.netfn = msg->rsp[6] >> 2;
			recv_msg->msg.cmd = msg->rsp[10];
			recv_msg->msg.data = recv_msg->msg_data;

			/*
			 * We chop off 12, not 11 bytes because the checksum
			 * at the end also needs to be removed.
			 */
			recv_msg->msg.data_len = msg->rsp_size - 12;
			memcpy(recv_msg->msg_data,
			       &(msg->rsp[11]),
			       msg->rsp_size - 12);
			deliver_response(recv_msg);
		}
	}

	return rv;
}