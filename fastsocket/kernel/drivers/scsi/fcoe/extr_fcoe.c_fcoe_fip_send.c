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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct fcoe_ctlr {int /*<<< orphan*/  lp; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 TYPE_1__* fcoe_from_ctlr (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_port_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  lport_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_fip_send(struct fcoe_ctlr *fip, struct sk_buff *skb)
{
	skb->dev = fcoe_from_ctlr(fip)->netdev;
	fcoe_port_send(lport_priv(fip->lp), skb);
}