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
struct cfq_queue {int dummy; } ;
struct cfq_data {struct cfq_queue* active_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cfq_slice_expired (struct cfq_data*,struct cfq_queue*,int) ; 

__attribute__((used)) static inline void cfq_slice_expired(struct cfq_data *cfqd, bool timed_out)
{
	struct cfq_queue *cfqq = cfqd->active_queue;

	if (cfqq)
		__cfq_slice_expired(cfqd, cfqq, timed_out);
}