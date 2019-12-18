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
struct sctp_ulpevent {struct sctp_association* asoc; int /*<<< orphan*/  rmem_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct sctp_association {TYPE_1__ base; int /*<<< orphan*/  rmem_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_association_hold (struct sctp_association*) ; 
 struct sk_buff* sctp_event2skb (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_skb_set_owner_r (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sctp_ulpevent_set_owner(struct sctp_ulpevent *event,
					   const struct sctp_association *asoc)
{
	struct sk_buff *skb;

	/* Cast away the const, as we are just wanting to
	 * bump the reference count.
	 */
	sctp_association_hold((struct sctp_association *)asoc);
	skb = sctp_event2skb(event);
	event->asoc = (struct sctp_association *)asoc;
	atomic_add(event->rmem_len, &event->asoc->rmem_alloc);
	sctp_skb_set_owner_r(skb, asoc->base.sk);
}