#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cpu_num; int lnum; int /*<<< orphan*/ ** caches; int /*<<< orphan*/  state; int /*<<< orphan*/  pnum; int /*<<< orphan*/ * package; int /*<<< orphan*/ * die; int /*<<< orphan*/ * core; int /*<<< orphan*/ * next_in_pkg; int /*<<< orphan*/ * next_in_die; int /*<<< orphan*/ * next_in_core; TYPE_2__* cpu; struct TYPE_4__* lcpu; } ;
typedef  TYPE_1__ x86_lcpu_t ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_phys_number; TYPE_1__ lcpu; } ;
typedef  TYPE_2__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCPU_OFF ; 
 int MAX_CACHE_DEPTH ; 
 TYPE_2__* cpu_datap (int) ; 

__attribute__((used)) static void
x86_lcpu_init(int cpu)
{
    cpu_data_t		*cpup;
    x86_lcpu_t		*lcpu;
    int			i;

    cpup = cpu_datap(cpu);

    lcpu = &cpup->lcpu;
    lcpu->lcpu = lcpu;
    lcpu->cpu  = cpup;
    lcpu->next_in_core = NULL;
    lcpu->next_in_die  = NULL;
    lcpu->next_in_pkg  = NULL;
    lcpu->core         = NULL;
    lcpu->die          = NULL;
    lcpu->package      = NULL;
    lcpu->cpu_num = cpu;
    lcpu->lnum = cpu;
    lcpu->pnum = cpup->cpu_phys_number;
    lcpu->state = LCPU_OFF;
    for (i = 0; i < MAX_CACHE_DEPTH; i += 1)
	lcpu->caches[i] = NULL;
}