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
struct sctp_ulpq {TYPE_2__* asoc; } ;
struct sctp_ulpevent {int msg_flags; scalar_t__ stream; scalar_t__ ssn; } ;
struct sctp_stream {int dummy; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_4__ {TYPE_1__* ssnmap; } ;
struct TYPE_3__ {struct sctp_stream in; } ;

/* Variables and functions */
 int SCTP_DATA_UNORDERED ; 
 int /*<<< orphan*/  sctp_ssn_next (struct sctp_stream*,scalar_t__) ; 
 scalar_t__ sctp_ssn_peek (struct sctp_stream*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_ulpq_retrieve_ordered (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpq_store_ordered (struct sctp_ulpq*,struct sctp_ulpevent*) ; 

__attribute__((used)) static struct sctp_ulpevent *sctp_ulpq_order(struct sctp_ulpq *ulpq,
					     struct sctp_ulpevent *event)
{
	__u16 sid, ssn;
	struct sctp_stream *in;

	/* Check if this message needs ordering.  */
	if (SCTP_DATA_UNORDERED & event->msg_flags)
		return event;

	/* Note: The stream ID must be verified before this routine.  */
	sid = event->stream;
	ssn = event->ssn;
	in  = &ulpq->asoc->ssnmap->in;

	/* Is this the expected SSN for this stream ID?  */
	if (ssn != sctp_ssn_peek(in, sid)) {
		/* We've received something out of order, so find where it
		 * needs to be placed.  We order by stream and then by SSN.
		 */
		sctp_ulpq_store_ordered(ulpq, event);
		return NULL;
	}

	/* Mark that the next chunk has been found.  */
	sctp_ssn_next(in, sid);

	/* Go find any other chunks that were waiting for
	 * ordering.
	 */
	sctp_ulpq_retrieve_ordered(ulpq, event);

	return event;
}