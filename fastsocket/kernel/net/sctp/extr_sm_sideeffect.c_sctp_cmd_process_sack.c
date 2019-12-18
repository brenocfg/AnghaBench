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
struct sctp_sackhdr {int dummy; } ;
struct sctp_association {int /*<<< orphan*/  ep; int /*<<< orphan*/  state; int /*<<< orphan*/  outqueue; } ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_EVENT_NO_PENDING_TSN ; 
 int /*<<< orphan*/  SCTP_EVENT_T_OTHER ; 
 int /*<<< orphan*/  SCTP_ST_OTHER (int /*<<< orphan*/ ) ; 
 int sctp_do_sm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_association*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_outq_sack (int /*<<< orphan*/ *,struct sctp_sackhdr*) ; 

__attribute__((used)) static int sctp_cmd_process_sack(sctp_cmd_seq_t *cmds,
				 struct sctp_association *asoc,
				 struct sctp_sackhdr *sackh)
{
	int err = 0;

	if (sctp_outq_sack(&asoc->outqueue, sackh)) {
		/* There are no more TSNs awaiting SACK.  */
		err = sctp_do_sm(SCTP_EVENT_T_OTHER,
				 SCTP_ST_OTHER(SCTP_EVENT_NO_PENDING_TSN),
				 asoc->state, asoc->ep, asoc, NULL,
				 GFP_ATOMIC);
	}

	return err;
}