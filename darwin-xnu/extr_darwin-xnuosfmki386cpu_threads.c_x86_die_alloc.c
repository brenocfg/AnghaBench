#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pdie_num; int /*<<< orphan*/  flags; int /*<<< orphan*/  ldie_num; struct TYPE_8__* next_in_pkg; } ;
typedef  TYPE_1__ x86_die_t ;
struct TYPE_9__ {int cpu_phys_number; } ;
typedef  TYPE_2__ cpu_data_t ;
struct TYPE_10__ {int nPThreadsPerDie; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86DIE_FL_PRESENT ; 
 int /*<<< orphan*/  atomic_incl (long*,int) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 TYPE_2__* cpu_datap (int) ; 
 TYPE_1__* free_dies ; 
 TYPE_1__* kalloc (int) ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_dies ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__ topoParms ; 
 int /*<<< orphan*/  x86_topo_lock ; 

__attribute__((used)) static x86_die_t *
x86_die_alloc(int cpu)
{
    x86_die_t	*die;
    cpu_data_t	*cpup;

    cpup = cpu_datap(cpu);

    mp_safe_spin_lock(&x86_topo_lock);
    if (free_dies != NULL) {
	die = free_dies;
	free_dies = die->next_in_pkg;
	die->next_in_pkg = NULL;
	simple_unlock(&x86_topo_lock);
    } else {
	simple_unlock(&x86_topo_lock);
	die = kalloc(sizeof(x86_die_t));
	if (die == NULL)
	    panic("x86_die_alloc() kalloc of x86_die_t failed!\n");
    }

    bzero((void *) die, sizeof(x86_die_t));

    die->pdie_num = cpup->cpu_phys_number / topoParms.nPThreadsPerDie;

    die->ldie_num = num_dies;
    atomic_incl((long *) &num_dies, 1);

    die->flags = X86DIE_FL_PRESENT;
    return(die);
}