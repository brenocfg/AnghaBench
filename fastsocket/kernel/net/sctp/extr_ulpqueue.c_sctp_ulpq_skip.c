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
struct sctp_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {TYPE_1__* ssnmap; } ;
struct TYPE_3__ {struct sctp_stream in; } ;

/* Variables and functions */
 scalar_t__ SSN_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ssn_peek (struct sctp_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ssn_skip (struct sctp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpq_reap_ordered (struct sctp_ulpq*,int /*<<< orphan*/ ) ; 

void sctp_ulpq_skip(struct sctp_ulpq *ulpq, __u16 sid, __u16 ssn)
{
	struct sctp_stream *in;

	/* Note: The stream ID must be verified before this routine.  */
	in  = &ulpq->asoc->ssnmap->in;

	/* Is this an old SSN?  If so ignore. */
	if (SSN_lt(ssn, sctp_ssn_peek(in, sid)))
		return;

	/* Mark that we are no longer expecting this SSN or lower. */
	sctp_ssn_skip(in, sid, ssn);

	/* Go find any other chunks that were waiting for
	 * ordering and deliver them if needed.
	 */
	sctp_ulpq_reap_ordered(ulpq, sid);
	return;
}