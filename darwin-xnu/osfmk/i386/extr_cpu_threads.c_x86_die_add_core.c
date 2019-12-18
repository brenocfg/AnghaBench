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
struct TYPE_5__ {int num_cores; TYPE_2__* cores; } ;
typedef  TYPE_1__ x86_die_t ;
struct TYPE_6__ {TYPE_1__* die; struct TYPE_6__* next_in_die; } ;
typedef  TYPE_2__ x86_core_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86_die_add_core(x86_die_t *die, x86_core_t *core)
{
    assert(die != NULL);
    assert(core != NULL);

    core->next_in_die = die->cores;
    core->die = die;
    die->cores = core;
    die->num_cores += 1;
}