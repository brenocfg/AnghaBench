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
struct sctp_ulpq {TYPE_2__* asoc; int /*<<< orphan*/  pd_mode; } ;
struct sctp_ulpevent {int msg_flags; int /*<<< orphan*/  tsn; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_3__ {int /*<<< orphan*/  tsn_map; } ;
struct TYPE_4__ {TYPE_1__ peer; } ;

/* Variables and functions */
 int MSG_EOR ; 
 int SCTP_DATA_FRAG_MASK ; 
 int SCTP_DATA_NOT_FRAG ; 
 scalar_t__ TSN_lte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_tsnmap_get_ctsn (int /*<<< orphan*/ *) ; 
 struct sctp_ulpevent* sctp_ulpq_retrieve_partial (struct sctp_ulpq*) ; 
 struct sctp_ulpevent* sctp_ulpq_retrieve_reassembled (struct sctp_ulpq*) ; 
 int /*<<< orphan*/  sctp_ulpq_store_reasm (struct sctp_ulpq*,struct sctp_ulpevent*) ; 

__attribute__((used)) static struct sctp_ulpevent *sctp_ulpq_reasm(struct sctp_ulpq *ulpq,
						struct sctp_ulpevent *event)
{
	struct sctp_ulpevent *retval = NULL;

	/* Check if this is part of a fragmented message.  */
	if (SCTP_DATA_NOT_FRAG == (event->msg_flags & SCTP_DATA_FRAG_MASK)) {
		event->msg_flags |= MSG_EOR;
		return event;
	}

	sctp_ulpq_store_reasm(ulpq, event);
	if (!ulpq->pd_mode)
		retval = sctp_ulpq_retrieve_reassembled(ulpq);
	else {
		__u32 ctsn, ctsnap;

		/* Do not even bother unless this is the next tsn to
		 * be delivered.
		 */
		ctsn = event->tsn;
		ctsnap = sctp_tsnmap_get_ctsn(&ulpq->asoc->peer.tsn_map);
		if (TSN_lte(ctsn, ctsnap))
			retval = sctp_ulpq_retrieve_partial(ulpq);
	}

	return retval;
}