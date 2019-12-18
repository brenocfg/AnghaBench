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
struct sctp_outq {int empty; scalar_t__ out_qlen; scalar_t__ malloced; scalar_t__ cork; scalar_t__ outstanding_bytes; scalar_t__ fast_rtx; int /*<<< orphan*/  abandoned; int /*<<< orphan*/  sacked; int /*<<< orphan*/  retransmit; int /*<<< orphan*/  control_chunk_list; int /*<<< orphan*/  out_chunk_list; struct sctp_association* asoc; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void sctp_outq_init(struct sctp_association *asoc, struct sctp_outq *q)
{
	q->asoc = asoc;
	INIT_LIST_HEAD(&q->out_chunk_list);
	INIT_LIST_HEAD(&q->control_chunk_list);
	INIT_LIST_HEAD(&q->retransmit);
	INIT_LIST_HEAD(&q->sacked);
	INIT_LIST_HEAD(&q->abandoned);

	q->fast_rtx = 0;
	q->outstanding_bytes = 0;
	q->empty = 1;
	q->cork  = 0;

	q->malloced = 0;
	q->out_qlen = 0;
}