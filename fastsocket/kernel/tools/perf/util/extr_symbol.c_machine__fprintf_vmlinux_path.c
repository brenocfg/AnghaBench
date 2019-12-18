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
struct machine {TYPE_1__** vmlinux_maps; } ;
struct dso {int has_build_id; } ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_2__ {struct dso* dso; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t MAP__FUNCTION ; 
 int PATH_MAX ; 
 scalar_t__ dso__build_id_filename (struct dso*,char*,int) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char** vmlinux_path ; 
 int vmlinux_path__nr_entries ; 

size_t machine__fprintf_vmlinux_path(struct machine *machine, FILE *fp)
{
	int i;
	size_t printed = 0;
	struct dso *kdso = machine->vmlinux_maps[MAP__FUNCTION]->dso;

	if (kdso->has_build_id) {
		char filename[PATH_MAX];
		if (dso__build_id_filename(kdso, filename, sizeof(filename)))
			printed += fprintf(fp, "[0] %s\n", filename);
	}

	for (i = 0; i < vmlinux_path__nr_entries; ++i)
		printed += fprintf(fp, "[%d] %s\n",
				   i + kdso->has_build_id, vmlinux_path[i]);

	return printed;
}