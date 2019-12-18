#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; TYPE_3__* dies; int /*<<< orphan*/  lpkg_num; int /*<<< orphan*/  ppkg_num; } ;
typedef  TYPE_1__ x86_pkg_t ;
struct TYPE_7__ {struct TYPE_7__* next_in_core; scalar_t__ primary; scalar_t__ master; int /*<<< orphan*/  lnum; int /*<<< orphan*/  pnum; int /*<<< orphan*/  cpu_num; } ;
typedef  TYPE_2__ x86_lcpu_t ;
struct TYPE_8__ {struct TYPE_8__* next_in_pkg; TYPE_4__* cores; int /*<<< orphan*/  ldie_num; int /*<<< orphan*/  pdie_num; } ;
typedef  TYPE_3__ x86_die_t ;
struct TYPE_9__ {struct TYPE_9__* next_in_die; TYPE_2__* lcpus; int /*<<< orphan*/  lcore_num; int /*<<< orphan*/  pcore_num; } ;
typedef  TYPE_4__ x86_core_t ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 TYPE_1__* x86_pkgs ; 

__attribute__((used)) static void
debug_topology_print(void)
{
    x86_pkg_t		*pkg;
    x86_die_t		*die;
    x86_core_t		*core;
    x86_lcpu_t		*cpu;

    pkg = x86_pkgs;
    while (pkg != NULL) {
	kprintf("Package:\n");
	kprintf("    Physical: %d\n", pkg->ppkg_num);
	kprintf("    Logical:  %d\n", pkg->lpkg_num);

	die = pkg->dies;
	while (die != NULL) {
	    kprintf("    Die:\n");
	    kprintf("        Physical: %d\n", die->pdie_num);
	    kprintf("        Logical:  %d\n", die->ldie_num);

	    core = die->cores;
	    while (core != NULL) {
		kprintf("        Core:\n");
		kprintf("            Physical: %d\n", core->pcore_num);
		kprintf("            Logical:  %d\n", core->lcore_num);

		cpu = core->lcpus;
		while (cpu != NULL) {
		    kprintf("            LCPU:\n");
		    kprintf("                CPU #:    %d\n", cpu->cpu_num);
		    kprintf("                Physical: %d\n", cpu->pnum);
		    kprintf("                Logical:  %d\n", cpu->lnum);
		    kprintf("                Flags:    ");
		    if (cpu->master)
			kprintf("MASTER ");
		    if (cpu->primary)
			kprintf("PRIMARY");
		    if (!cpu->master && !cpu->primary)
			kprintf("(NONE)");
		    kprintf("\n");

		    cpu = cpu->next_in_core;
		}

		core = core->next_in_die;
	    }

	    die = die->next_in_pkg;
	}

	pkg = pkg->next;
    }
}