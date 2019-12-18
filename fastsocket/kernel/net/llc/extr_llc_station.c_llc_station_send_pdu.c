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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_pdu_q; } ;

/* Variables and functions */
 scalar_t__ dev_queue_xmit (struct sk_buff*) ; 
 TYPE_1__ llc_main_station ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void llc_station_send_pdu(struct sk_buff *skb)
{
	skb_queue_tail(&llc_main_station.mac_pdu_q, skb);
	while ((skb = skb_dequeue(&llc_main_station.mac_pdu_q)) != NULL)
		if (dev_queue_xmit(skb))
			break;
}