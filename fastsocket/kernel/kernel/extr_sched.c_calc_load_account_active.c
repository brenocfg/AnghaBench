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
struct rq {long nr_running; long calc_load_active; scalar_t__ nr_uninterruptible; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_add (long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calc_load_tasks ; 

__attribute__((used)) static void calc_load_account_active(struct rq *this_rq)
{
	long nr_active, delta;

	nr_active = this_rq->nr_running;
	nr_active += (long) this_rq->nr_uninterruptible;

	if (nr_active != this_rq->calc_load_active) {
		delta = nr_active - this_rq->calc_load_active;
		this_rq->calc_load_active = nr_active;
		atomic_long_add(delta, &calc_load_tasks);
	}
}