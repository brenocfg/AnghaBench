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
struct cfil_queue {size_t q_end; int /*<<< orphan*/  q_mq; } ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFIL_QUEUE_VERIFY (struct cfil_queue*) ; 
 int /*<<< orphan*/  MBUFQ_ENQUEUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cfil_queue_enqueue(struct cfil_queue *cfq, mbuf_t m, size_t len)
{
	CFIL_QUEUE_VERIFY(cfq);

	MBUFQ_ENQUEUE(&cfq->q_mq, m);
	cfq->q_end += len;

	CFIL_QUEUE_VERIFY(cfq);
}