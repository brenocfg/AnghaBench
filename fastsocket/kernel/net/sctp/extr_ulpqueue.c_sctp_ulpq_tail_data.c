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
struct sctp_ulpq {int dummy; } ;
struct sctp_ulpevent {int msg_flags; } ;
struct sctp_chunk {int /*<<< orphan*/  asoc; scalar_t__ chunk_hdr; } ;
typedef  int /*<<< orphan*/  sctp_data_chunk_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int MSG_EOR ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_rcvmsg (int /*<<< orphan*/ ,struct sctp_chunk*,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_ulpq_order (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpq_reasm (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpq_tail_event (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 

int sctp_ulpq_tail_data(struct sctp_ulpq *ulpq, struct sctp_chunk *chunk,
			gfp_t gfp)
{
	struct sk_buff_head temp;
	sctp_data_chunk_t *hdr;
	struct sctp_ulpevent *event;

	hdr = (sctp_data_chunk_t *) chunk->chunk_hdr;

	/* Create an event from the incoming chunk. */
	event = sctp_ulpevent_make_rcvmsg(chunk->asoc, chunk, gfp);
	if (!event)
		return -ENOMEM;

	/* Do reassembly if needed.  */
	event = sctp_ulpq_reasm(ulpq, event);

	/* Do ordering if needed.  */
	if ((event) && (event->msg_flags & MSG_EOR)){
		/* Create a temporary list to collect chunks on.  */
		skb_queue_head_init(&temp);
		__skb_queue_tail(&temp, sctp_event2skb(event));

		event = sctp_ulpq_order(ulpq, event);
	}

	/* Send event to the ULP.  'event' is the sctp_ulpevent for
	 * very first SKB on the 'temp' list.
	 */
	if (event)
		sctp_ulpq_tail_event(ulpq, event);

	return 0;
}