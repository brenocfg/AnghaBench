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
struct cfil_queue {int /*<<< orphan*/  q_mq; } ;

/* Variables and functions */
 int MBUFQ_EMPTY (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
cfil_queue_empty(struct cfil_queue *cfq)
{
	return (MBUFQ_EMPTY(&cfq->q_mq));
}