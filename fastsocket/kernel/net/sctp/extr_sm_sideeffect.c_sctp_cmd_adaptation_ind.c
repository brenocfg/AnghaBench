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
struct sctp_ulpevent {int dummy; } ;
struct sctp_association {int /*<<< orphan*/  ulpq; } ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sctp_ulpevent* sctp_ulpevent_make_adaptation_indication (struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpq_tail_event (int /*<<< orphan*/ *,struct sctp_ulpevent*) ; 

__attribute__((used)) static void sctp_cmd_adaptation_ind(sctp_cmd_seq_t *commands,
				    struct sctp_association *asoc)
{
	struct sctp_ulpevent *ev;

	ev = sctp_ulpevent_make_adaptation_indication(asoc, GFP_ATOMIC);

	if (ev)
		sctp_ulpq_tail_event(&asoc->ulpq, ev);
}