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
struct TYPE_3__ {scalar_t__* sndcount; struct sk_buff_head* bqueue; } ;
typedef  TYPE_1__ isdnloop_card ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_purge (struct sk_buff_head*) ; 

__attribute__((used)) static void
isdnloop_free_queue(isdnloop_card * card, int channel)
{
	struct sk_buff_head *queue = &card->bqueue[channel];

	skb_queue_purge(queue);
	card->sndcount[channel] = 0;
}