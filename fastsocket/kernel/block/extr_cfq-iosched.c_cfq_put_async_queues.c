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
struct cfq_data {scalar_t__ async_idle_cfqq; scalar_t__** async_cfqq; } ;

/* Variables and functions */
 int IOPRIO_BE_NR ; 
 int /*<<< orphan*/  cfq_put_queue (scalar_t__) ; 

__attribute__((used)) static void cfq_put_async_queues(struct cfq_data *cfqd)
{
	int i;

	for (i = 0; i < IOPRIO_BE_NR; i++) {
		if (cfqd->async_cfqq[0][i])
			cfq_put_queue(cfqd->async_cfqq[0][i]);
		if (cfqd->async_cfqq[1][i])
			cfq_put_queue(cfqd->async_cfqq[1][i]);
	}

	if (cfqd->async_idle_cfqq)
		cfq_put_queue(cfqd->async_idle_cfqq);
}