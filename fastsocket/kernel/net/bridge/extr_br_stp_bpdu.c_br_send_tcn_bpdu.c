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
struct net_bridge_port {TYPE_1__* br; } ;
struct TYPE_2__ {scalar_t__ stp_enabled; } ;

/* Variables and functions */
 unsigned char BPDU_TYPE_TCN ; 
 scalar_t__ BR_KERNEL_STP ; 
 int /*<<< orphan*/  br_send_bpdu (struct net_bridge_port*,unsigned char*,int) ; 

void br_send_tcn_bpdu(struct net_bridge_port *p)
{
	unsigned char buf[4];

	if (p->br->stp_enabled != BR_KERNEL_STP)
		return;

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = BPDU_TYPE_TCN;
	br_send_bpdu(p, buf, 4);
}