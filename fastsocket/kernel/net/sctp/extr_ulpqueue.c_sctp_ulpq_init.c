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
struct sctp_ulpq {scalar_t__ malloced; scalar_t__ pd_mode; int /*<<< orphan*/  lobby; int /*<<< orphan*/  reasm; struct sctp_association* asoc; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct sctp_ulpq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

struct sctp_ulpq *sctp_ulpq_init(struct sctp_ulpq *ulpq,
				 struct sctp_association *asoc)
{
	memset(ulpq, 0, sizeof(struct sctp_ulpq));

	ulpq->asoc = asoc;
	skb_queue_head_init(&ulpq->reasm);
	skb_queue_head_init(&ulpq->lobby);
	ulpq->pd_mode  = 0;
	ulpq->malloced = 0;

	return ulpq;
}