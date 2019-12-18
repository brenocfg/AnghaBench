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
struct task_struct {int dummy; } ;
struct svc_pool_map {unsigned int* pool_to; scalar_t__ count; int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  SVC_POOL_PERCPU 129 
#define  SVC_POOL_PERNODE 128 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  cpumask_of_node (unsigned int) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct svc_pool_map svc_pool_map ; 

__attribute__((used)) static inline void
svc_pool_map_set_cpumask(struct task_struct *task, unsigned int pidx)
{
	struct svc_pool_map *m = &svc_pool_map;
	unsigned int node = m->pool_to[pidx];

	/*
	 * The caller checks for sv_nrpools > 1, which
	 * implies that we've been initialized.
	 */
	BUG_ON(m->count == 0);

	switch (m->mode) {
	case SVC_POOL_PERCPU:
	{
		set_cpus_allowed_ptr(task, cpumask_of(node));
		break;
	}
	case SVC_POOL_PERNODE:
	{
		set_cpus_allowed_ptr(task, cpumask_of_node(node));
		break;
	}
	}
}