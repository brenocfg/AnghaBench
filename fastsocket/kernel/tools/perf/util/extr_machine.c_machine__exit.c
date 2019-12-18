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
struct machine {int /*<<< orphan*/ * root_dir; int /*<<< orphan*/  kernel_dsos; int /*<<< orphan*/  user_dsos; int /*<<< orphan*/  kmaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsos__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_groups__exit (int /*<<< orphan*/ *) ; 

void machine__exit(struct machine *machine)
{
	map_groups__exit(&machine->kmaps);
	dsos__delete(&machine->user_dsos);
	dsos__delete(&machine->kernel_dsos);
	free(machine->root_dir);
	machine->root_dir = NULL;
}