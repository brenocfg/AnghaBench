#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct fcoe_ctlr {int /*<<< orphan*/  recv_work; int /*<<< orphan*/  fip_recv_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void fcoe_ctlr_recv(struct fcoe_ctlr *fip, struct sk_buff *skb)
{
	skb_queue_tail(&fip->fip_recv_list, skb);
	schedule_work(&fip->recv_work);
}