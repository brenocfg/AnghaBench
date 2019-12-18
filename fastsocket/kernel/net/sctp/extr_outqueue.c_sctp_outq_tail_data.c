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
struct sctp_outq {int /*<<< orphan*/  out_qlen; int /*<<< orphan*/  out_chunk_list; } ;
struct sctp_chunk {TYPE_1__* skb; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sctp_outq_tail_data(struct sctp_outq *q,
				       struct sctp_chunk *ch)
{
	list_add_tail(&ch->list, &q->out_chunk_list);
	q->out_qlen += ch->skb->len;
	return;
}