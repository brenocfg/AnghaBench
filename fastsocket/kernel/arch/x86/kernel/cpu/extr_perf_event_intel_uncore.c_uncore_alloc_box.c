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
struct intel_uncore_type {int num_shared_regs; } ;
struct intel_uncore_extra_reg {int dummy; } ;
struct intel_uncore_box {int cpu; int phys_id; int /*<<< orphan*/  refcnt; TYPE_1__* shared_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 struct intel_uncore_box* kmalloc_node (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uncore_pmu_init_hrtimer (struct intel_uncore_box*) ; 

struct intel_uncore_box *uncore_alloc_box(struct intel_uncore_type *type, int cpu)
{
	struct intel_uncore_box *box;
	int i, size;

	size = sizeof(*box) + type->num_shared_regs * sizeof(struct intel_uncore_extra_reg);

	box = kmalloc_node(size, GFP_KERNEL | __GFP_ZERO, cpu_to_node(cpu));
	if (!box)
		return NULL;

	for (i = 0; i < type->num_shared_regs; i++)
		spin_lock_init(&box->shared_regs[i].lock);

	uncore_pmu_init_hrtimer(box);
	atomic_set(&box->refcnt, 1);
	box->cpu = -1;
	box->phys_id = -1;

	return box;
}