#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct amd_nb {int nb_id; TYPE_1__* event_constraints; } ;
struct TYPE_4__ {int num_counters; } ;
struct TYPE_3__ {int weight; int /*<<< orphan*/  idxmsk; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 struct amd_nb* kmalloc_node (int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static struct amd_nb *amd_alloc_nb(int cpu)
{
	struct amd_nb *nb;
	int i;

	nb = kmalloc_node(sizeof(struct amd_nb), GFP_KERNEL | __GFP_ZERO,
			  cpu_to_node(cpu));
	if (!nb)
		return NULL;

	nb->nb_id = -1;

	/*
	 * initialize all possible NB constraints
	 */
	for (i = 0; i < x86_pmu.num_counters; i++) {
		__set_bit(i, nb->event_constraints[i].idxmsk);
		nb->event_constraints[i].weight = 1;
	}
	return nb;
}