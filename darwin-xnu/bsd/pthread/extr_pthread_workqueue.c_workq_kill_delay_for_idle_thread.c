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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint16_t ;
struct workqueue {scalar_t__ wq_thidlecount; } ;
struct TYPE_2__ {scalar_t__ abstime; } ;

/* Variables and functions */
 scalar_t__ wq_death_max_load ; 
 scalar_t__ wq_max_constrained_threads ; 
 TYPE_1__ wq_reduce_pool_window ; 

__attribute__((used)) static inline uint64_t
workq_kill_delay_for_idle_thread(struct workqueue *wq)
{
	uint64_t delay = wq_reduce_pool_window.abstime;
	uint16_t idle = wq->wq_thidlecount;

	/*
	 * If we have less than wq_death_max_load threads, have a 5s timer.
	 *
	 * For the next wq_max_constrained_threads ones, decay linearly from
	 * from 5s to 50ms.
	 */
	if (idle <= wq_death_max_load) {
		return delay;
	}

	if (wq_max_constrained_threads > idle - wq_death_max_load) {
		delay *= (wq_max_constrained_threads - (idle - wq_death_max_load));
	}
	return delay / wq_max_constrained_threads;
}