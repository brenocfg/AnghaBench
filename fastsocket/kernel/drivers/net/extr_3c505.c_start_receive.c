#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct Rcv_pkt {int dummy; } ;
struct TYPE_8__ {int buf_len; scalar_t__ timeout; scalar_t__ buf_ofs; scalar_t__ buf_seg; } ;
struct TYPE_9__ {TYPE_1__ rcv_pkt; } ;
struct TYPE_10__ {int length; TYPE_2__ data; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ pcb_struct ;
struct TYPE_11__ {int /*<<< orphan*/  rx_active; } ;
typedef  TYPE_4__ elp_device ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RECEIVE_PACKET ; 
 int elp_debug ; 
 TYPE_4__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int send_pcb (struct net_device*,TYPE_3__*) ; 

__attribute__((used)) static bool start_receive(struct net_device *dev, pcb_struct * tx_pcb)
{
	bool status;
	elp_device *adapter = netdev_priv(dev);

	if (elp_debug >= 3)
		pr_debug("%s: restarting receiver\n", dev->name);
	tx_pcb->command = CMD_RECEIVE_PACKET;
	tx_pcb->length = sizeof(struct Rcv_pkt);
	tx_pcb->data.rcv_pkt.buf_seg
	    = tx_pcb->data.rcv_pkt.buf_ofs = 0;		/* Unused */
	tx_pcb->data.rcv_pkt.buf_len = 1600;
	tx_pcb->data.rcv_pkt.timeout = 0;	/* set timeout to zero */
	status = send_pcb(dev, tx_pcb);
	if (status)
		adapter->rx_active++;
	return status;
}