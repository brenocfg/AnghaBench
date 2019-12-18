#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {struct sk_buff** xskb; scalar_t__* sndcount; scalar_t__* xlen; struct sk_buff_head* spqueue; } ;
typedef  TYPE_1__ icn_card ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_purge (struct sk_buff_head*) ; 

__attribute__((used)) static void
icn_free_queue(icn_card * card, int channel)
{
	struct sk_buff_head *queue = &card->spqueue[channel];
	struct sk_buff *skb;

	skb_queue_purge(queue);
	card->xlen[channel] = 0;
	card->sndcount[channel] = 0;
	if ((skb = card->xskb[channel])) {
		card->xskb[channel] = NULL;
		dev_kfree_skb(skb);
	}
}