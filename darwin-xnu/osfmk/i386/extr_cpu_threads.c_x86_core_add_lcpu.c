#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* core; struct TYPE_5__* next_in_core; } ;
typedef  TYPE_1__ x86_lcpu_t ;
struct TYPE_6__ {int num_lcpus; TYPE_1__* lcpus; } ;
typedef  TYPE_2__ x86_core_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_topo_lock ; 

__attribute__((used)) static void
x86_core_add_lcpu(x86_core_t *core, x86_lcpu_t *lcpu)
{
    assert(core != NULL);
    assert(lcpu != NULL);

    mp_safe_spin_lock(&x86_topo_lock);

    lcpu->next_in_core = core->lcpus;
    lcpu->core = core;
    core->lcpus = lcpu;
    core->num_lcpus += 1;
    simple_unlock(&x86_topo_lock);
}