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
typedef  int /*<<< orphan*/  u8 ;
struct sctp_ulpevent {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sinit_max_instreams; int /*<<< orphan*/  sinit_num_ostreams; } ;
struct sctp_association {int /*<<< orphan*/  ulpq; TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sctp_ulpevent* sctp_ulpevent_make_assoc_change (struct sctp_association*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpq_tail_event (int /*<<< orphan*/ *,struct sctp_ulpevent*) ; 

__attribute__((used)) static void sctp_cmd_assoc_change(sctp_cmd_seq_t *commands,
				 struct sctp_association *asoc,
				 u8 state)
{
	struct sctp_ulpevent *ev;

	ev = sctp_ulpevent_make_assoc_change(asoc, 0, state, 0,
					    asoc->c.sinit_num_ostreams,
					    asoc->c.sinit_max_instreams,
					    NULL, GFP_ATOMIC);
	if (ev)
		sctp_ulpq_tail_event(&asoc->ulpq, ev);
}