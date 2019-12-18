#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int default_out_queue; int no_out_queues; int /*<<< orphan*/  do_prio_queueing; } ;
struct TYPE_4__ {scalar_t__ type; int is_multicast_different; } ;
struct qeth_card {TYPE_2__ qdio; TYPE_1__ info; } ;
struct TYPE_6__ {int tos; } ;

/* Variables and functions */
 int const IP_TOS_HIGHRELIABILITY ; 
 int const IP_TOS_HIGHTHROUGHPUT ; 
 int const IP_TOS_LOWDELAY ; 
 int const IP_TOS_NOTIMPORTANT ; 
 scalar_t__ QETH_CARD_TYPE_OSD ; 
 scalar_t__ QETH_CARD_TYPE_OSX ; 
 int /*<<< orphan*/  QETH_PRIO_Q_ING_PREC ; 
 int /*<<< orphan*/  QETH_PRIO_Q_ING_TOS ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 

int qeth_get_priority_queue(struct qeth_card *card, struct sk_buff *skb,
			int ipv, int cast_type)
{
	if (!ipv && (card->info.type == QETH_CARD_TYPE_OSD ||
		     card->info.type == QETH_CARD_TYPE_OSX))
		return card->qdio.default_out_queue;
	switch (card->qdio.no_out_queues) {
	case 4:
		if (cast_type && card->info.is_multicast_different)
			return card->info.is_multicast_different &
				(card->qdio.no_out_queues - 1);
		if (card->qdio.do_prio_queueing && (ipv == 4)) {
			const u8 tos = ip_hdr(skb)->tos;

			if (card->qdio.do_prio_queueing ==
				QETH_PRIO_Q_ING_TOS) {
				if (tos & IP_TOS_NOTIMPORTANT)
					return 3;
				if (tos & IP_TOS_HIGHRELIABILITY)
					return 2;
				if (tos & IP_TOS_HIGHTHROUGHPUT)
					return 1;
				if (tos & IP_TOS_LOWDELAY)
					return 0;
			}
			if (card->qdio.do_prio_queueing ==
				QETH_PRIO_Q_ING_PREC)
				return 3 - (tos >> 6);
		} else if (card->qdio.do_prio_queueing && (ipv == 6)) {
			/* TODO: IPv6!!! */
		}
		return card->qdio.default_out_queue;
	case 1: /* fallthrough for single-out-queue 1920-device */
	default:
		return card->qdio.default_out_queue;
	}
}