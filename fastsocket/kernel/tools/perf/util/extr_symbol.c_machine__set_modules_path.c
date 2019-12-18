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
struct machine {char* root_dir; int /*<<< orphan*/  kmaps; } ;
typedef  int /*<<< orphan*/  modules_path ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_kernel_version (char*) ; 
 int map_groups__set_modules_path_dir (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int machine__set_modules_path(struct machine *machine)
{
	char *version;
	char modules_path[PATH_MAX];

	version = get_kernel_version(machine->root_dir);
	if (!version)
		return -1;

	snprintf(modules_path, sizeof(modules_path), "%s/lib/modules/%s/kernel",
		 machine->root_dir, version);
	free(version);

	return map_groups__set_modules_path_dir(&machine->kmaps, modules_path);
}