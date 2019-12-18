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
struct TYPE_2__ {int nr_sbal_error; int nr_sbal_total; } ;
struct qdio_q {TYPE_1__ q_stats; } ;

/* Variables and functions */

__attribute__((used)) static inline void account_sbals_error(struct qdio_q *q, int count)
{
	q->q_stats.nr_sbal_error += count;
	q->q_stats.nr_sbal_total += count;
}