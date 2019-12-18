#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sctp_ulpq {TYPE_2__* asoc; } ;
struct sctp_ulpevent {int /*<<< orphan*/  tsn; } ;
struct sctp_tsnmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  scalar_t__ __u16 ;
struct TYPE_3__ {struct sctp_tsnmap tsn_map; } ;
struct TYPE_4__ {TYPE_1__ peer; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue_tail (struct sk_buff_head*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_tsnmap_renege (struct sctp_tsnmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_free (struct sctp_ulpevent*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 

__attribute__((used)) static __u16 sctp_ulpq_renege_list(struct sctp_ulpq *ulpq,
		struct sk_buff_head *list, __u16 needed)
{
	__u16 freed = 0;
	__u32 tsn;
	struct sk_buff *skb;
	struct sctp_ulpevent *event;
	struct sctp_tsnmap *tsnmap;

	tsnmap = &ulpq->asoc->peer.tsn_map;

	while ((skb = __skb_dequeue_tail(list)) != NULL) {
		freed += skb_headlen(skb);
		event = sctp_skb2event(skb);
		tsn = event->tsn;

		sctp_ulpevent_free(event);
		sctp_tsnmap_renege(tsnmap, tsn);
		if (freed >= needed)
			return freed;
	}

	return freed;
}