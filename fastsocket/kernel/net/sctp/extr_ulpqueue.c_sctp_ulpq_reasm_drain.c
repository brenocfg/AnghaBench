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
struct sk_buff_head {int dummy; } ;
struct sctp_ulpq {int /*<<< orphan*/  reasm; } ;
struct sctp_ulpevent {int msg_flags; } ;

/* Variables and functions */
 int MSG_EOR ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpq_order (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpq_retrieve_reassembled (struct sctp_ulpq*) ; 
 int /*<<< orphan*/  sctp_ulpq_tail_event (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 

__attribute__((used)) static void sctp_ulpq_reasm_drain(struct sctp_ulpq *ulpq)
{
	struct sctp_ulpevent *event = NULL;
	struct sk_buff_head temp;

	if (skb_queue_empty(&ulpq->reasm))
		return;

	while ((event = sctp_ulpq_retrieve_reassembled(ulpq)) != NULL) {
		/* Do ordering if needed.  */
		if ((event) && (event->msg_flags & MSG_EOR)){
			skb_queue_head_init(&temp);
			__skb_queue_tail(&temp, sctp_event2skb(event));

			event = sctp_ulpq_order(ulpq, event);
		}

		/* Send event to the ULP.  'event' is the
		 * sctp_ulpevent for  very first SKB on the  temp' list.
		 */
		if (event)
			sctp_ulpq_tail_event(ulpq, event);
	}
}