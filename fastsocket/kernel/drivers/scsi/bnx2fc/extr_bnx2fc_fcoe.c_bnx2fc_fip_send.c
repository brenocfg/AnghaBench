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
struct fcoe_ctlr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 TYPE_1__* bnx2fc_from_ctlr (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 

__attribute__((used)) static void bnx2fc_fip_send(struct fcoe_ctlr *fip, struct sk_buff *skb)
{
	skb->dev = bnx2fc_from_ctlr(fip)->netdev;
	dev_queue_xmit(skb);
}