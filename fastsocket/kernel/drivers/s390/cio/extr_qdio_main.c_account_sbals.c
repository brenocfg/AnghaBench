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
struct TYPE_2__ {int nr_sbal_total; int /*<<< orphan*/ * nr_sbals; } ;
struct qdio_q {TYPE_1__ q_stats; } ;

/* Variables and functions */
 int QDIO_MAX_BUFFERS_MASK ; 

__attribute__((used)) static inline void account_sbals(struct qdio_q *q, int count)
{
	int pos = 0;

	q->q_stats.nr_sbal_total += count;
	if (count == QDIO_MAX_BUFFERS_MASK) {
		q->q_stats.nr_sbals[7]++;
		return;
	}
	while (count >>= 1)
		pos++;
	q->q_stats.nr_sbals[pos]++;
}