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
struct cpumask {int dummy; } ;
struct cpu_stop_done {int ret; scalar_t__ executed; int /*<<< orphan*/  completion; } ;
typedef  int /*<<< orphan*/  cpu_stop_fn_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  cpu_stop_init_done (struct cpu_stop_done*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_weight (struct cpumask const*) ; 
 int /*<<< orphan*/  queue_stop_cpus_work (struct cpumask const*,int /*<<< orphan*/ ,void*,struct cpu_stop_done*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __stop_cpus(const struct cpumask *cpumask,
		       cpu_stop_fn_t fn, void *arg)
{
	struct cpu_stop_done done;

	cpu_stop_init_done(&done, cpumask_weight(cpumask));
	queue_stop_cpus_work(cpumask, fn, arg, &done);
	wait_for_completion(&done.completion);
	return done.executed ? done.ret : -ENOENT;
}