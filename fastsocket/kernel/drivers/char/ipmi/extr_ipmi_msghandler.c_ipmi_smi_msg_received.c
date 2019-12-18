#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ipmi_smi_msg {int data_size; int* data; int rsp_size; int* rsp; int /*<<< orphan*/  link; int /*<<< orphan*/  msgid; int /*<<< orphan*/ * user_data; } ;
typedef  TYPE_2__* ipmi_smi_t ;
struct TYPE_8__ {int run_to_completion; int /*<<< orphan*/  recv_tasklet; int /*<<< orphan*/  waiting_msgs_lock; int /*<<< orphan*/  waiting_msgs; TYPE_1__* channels; } ;
struct TYPE_7__ {scalar_t__ medium; } ;

/* Variables and functions */
 int IPMI_BUS_ERR ; 
 scalar_t__ IPMI_CHANNEL_MEDIUM_8023LAN ; 
 scalar_t__ IPMI_CHANNEL_MEDIUM_ASYNC ; 
 int IPMI_LOST_ARBITRATION_ERR ; 
 int IPMI_MAX_CHANNELS ; 
 int IPMI_NAK_ON_WRITE_ERR ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_NODE_BUSY_ERR ; 
 int IPMI_SEND_MSG_CMD ; 
 int /*<<< orphan*/  intf_err_seq (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intf_start_seq_timer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_free_smi_msg (struct ipmi_smi_msg*) ; 
 int /*<<< orphan*/  ipmi_inc_stat (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sent_ipmb_command_errs ; 
 int /*<<< orphan*/  sent_lan_command_errs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void ipmi_smi_msg_received(ipmi_smi_t          intf,
			   struct ipmi_smi_msg *msg)
{
	unsigned long flags = 0; /* keep us warning-free. */
	int           run_to_completion;


	if ((msg->data_size >= 2)
	    && (msg->data[0] == (IPMI_NETFN_APP_REQUEST << 2))
	    && (msg->data[1] == IPMI_SEND_MSG_CMD)
	    && (msg->user_data == NULL)) {
		/*
		 * This is the local response to a command send, start
		 * the timer for these.  The user_data will not be
		 * NULL if this is a response send, and we will let
		 * response sends just go through.
		 */

		/*
		 * Check for errors, if we get certain errors (ones
		 * that mean basically we can try again later), we
		 * ignore them and start the timer.  Otherwise we
		 * report the error immediately.
		 */
		if ((msg->rsp_size >= 3) && (msg->rsp[2] != 0)
		    && (msg->rsp[2] != IPMI_NODE_BUSY_ERR)
		    && (msg->rsp[2] != IPMI_LOST_ARBITRATION_ERR)
		    && (msg->rsp[2] != IPMI_BUS_ERR)
		    && (msg->rsp[2] != IPMI_NAK_ON_WRITE_ERR)) {
			int chan = msg->rsp[3] & 0xf;

			/* Got an error sending the message, handle it. */
			if (chan >= IPMI_MAX_CHANNELS)
				; /* This shouldn't happen */
			else if ((intf->channels[chan].medium
				  == IPMI_CHANNEL_MEDIUM_8023LAN)
				 || (intf->channels[chan].medium
				     == IPMI_CHANNEL_MEDIUM_ASYNC))
				ipmi_inc_stat(intf, sent_lan_command_errs);
			else
				ipmi_inc_stat(intf, sent_ipmb_command_errs);
			intf_err_seq(intf, msg->msgid, msg->rsp[2]);
		} else
			/* The message was sent, start the timer. */
			intf_start_seq_timer(intf, msg->msgid);

		ipmi_free_smi_msg(msg);
		goto out;
	}

	/*
	 * To preserve message order, if the list is not empty, we
	 * tack this message onto the end of the list.
	 */
	run_to_completion = intf->run_to_completion;
	if (!run_to_completion)
		spin_lock_irqsave(&intf->waiting_msgs_lock, flags);
	list_add_tail(&msg->link, &intf->waiting_msgs);
	if (!run_to_completion)
		spin_unlock_irqrestore(&intf->waiting_msgs_lock, flags);

	tasklet_schedule(&intf->recv_tasklet);
 out:
	return;
}