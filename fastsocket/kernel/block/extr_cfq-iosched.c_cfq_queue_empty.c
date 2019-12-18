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
struct request_queue {TYPE_1__* elevator; } ;
struct cfq_data {int /*<<< orphan*/  rq_queued; } ;
struct TYPE_2__ {struct cfq_data* elevator_data; } ;

/* Variables and functions */

__attribute__((used)) static int cfq_queue_empty(struct request_queue *q)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;

	return !cfqd->rq_queued;
}