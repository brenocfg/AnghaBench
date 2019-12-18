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
struct cfq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cfq_set_active_queue (struct cfq_data*,struct cfq_queue*) ; 
 struct cfq_queue* cfq_get_next_queue (struct cfq_data*) ; 

__attribute__((used)) static struct cfq_queue *cfq_set_active_queue(struct cfq_data *cfqd,
					      struct cfq_queue *cfqq)
{
	if (!cfqq)
		cfqq = cfq_get_next_queue(cfqd);

	__cfq_set_active_queue(cfqd, cfqq);
	return cfqq;
}