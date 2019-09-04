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
struct cfil_queue {int /*<<< orphan*/  q_mq; scalar_t__ q_end; scalar_t__ q_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUFQ_INIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
cfil_queue_init(struct cfil_queue *cfq)
{
	cfq->q_start = 0;
	cfq->q_end = 0;
	MBUFQ_INIT(&cfq->q_mq);
}