#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {short channel; } ;
struct TYPE_6__ {unsigned char cmd; unsigned char netfn; } ;
struct ipmi_recv_msg {TYPE_4__ addr; TYPE_1__ msg; } ;
struct ipmi_addr {int dummy; } ;
typedef  TYPE_3__* ipmi_smi_t ;
struct TYPE_8__ {int /*<<< orphan*/  seq_lock; TYPE_2__* seq_table; } ;
struct TYPE_7__ {scalar_t__ inuse; struct ipmi_recv_msg* recv_msg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 unsigned char IPMI_IPMB_NUM_SEQ ; 
 scalar_t__ ipmi_addr_equal (struct ipmi_addr*,TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int intf_find_seq(ipmi_smi_t           intf,
			 unsigned char        seq,
			 short                channel,
			 unsigned char        cmd,
			 unsigned char        netfn,
			 struct ipmi_addr     *addr,
			 struct ipmi_recv_msg **recv_msg)
{
	int           rv = -ENODEV;
	unsigned long flags;

	if (seq >= IPMI_IPMB_NUM_SEQ)
		return -EINVAL;

	spin_lock_irqsave(&(intf->seq_lock), flags);
	if (intf->seq_table[seq].inuse) {
		struct ipmi_recv_msg *msg = intf->seq_table[seq].recv_msg;

		if ((msg->addr.channel == channel) && (msg->msg.cmd == cmd)
				&& (msg->msg.netfn == netfn)
				&& (ipmi_addr_equal(addr, &(msg->addr)))) {
			*recv_msg = msg;
			intf->seq_table[seq].inuse = 0;
			rv = 0;
		}
	}
	spin_unlock_irqrestore(&(intf->seq_lock), flags);

	return rv;
}