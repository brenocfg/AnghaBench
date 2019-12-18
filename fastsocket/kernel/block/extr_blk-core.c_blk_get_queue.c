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
struct request_queue {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_dead (struct request_queue*) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 

int blk_get_queue(struct request_queue *q)
{
	if (likely(!blk_queue_dead(q))) {
		kobject_get(&q->kobj);
		return 0;
	}

	return 1;
}