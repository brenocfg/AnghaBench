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
typedef  int /*<<< orphan*/  u64 ;
struct map {int /*<<< orphan*/  dso; } ;
struct machine {char* root_dir; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {char* default_guest_modules; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  dso__kernel_module_get_build_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hex2u64 (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ machine__is_default_guest (struct machine*) ; 
 struct map* machine__new_module (struct machine*,int /*<<< orphan*/ ,char*) ; 
 int machine__set_modules_path (struct machine*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ symbol__restricted_filename (char*,char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int machine__create_modules(struct machine *machine)
{
	char *line = NULL;
	size_t n;
	FILE *file;
	struct map *map;
	const char *modules;
	char path[PATH_MAX];

	if (machine__is_default_guest(machine))
		modules = symbol_conf.default_guest_modules;
	else {
		sprintf(path, "%s/proc/modules", machine->root_dir);
		modules = path;
	}

	if (symbol__restricted_filename(path, "/proc/modules"))
		return -1;

	file = fopen(modules, "r");
	if (file == NULL)
		return -1;

	while (!feof(file)) {
		char name[PATH_MAX];
		u64 start;
		char *sep;
		int line_len;

		line_len = getline(&line, &n, file);
		if (line_len < 0)
			break;

		if (!line)
			goto out_failure;

		line[--line_len] = '\0'; /* \n */

		sep = strrchr(line, 'x');
		if (sep == NULL)
			continue;

		hex2u64(sep + 1, &start);

		sep = strchr(line, ' ');
		if (sep == NULL)
			continue;

		*sep = '\0';

		snprintf(name, sizeof(name), "[%s]", line);
		map = machine__new_module(machine, start, name);
		if (map == NULL)
			goto out_delete_line;
		dso__kernel_module_get_build_id(map->dso, machine->root_dir);
	}

	free(line);
	fclose(file);

	return machine__set_modules_path(machine);

out_delete_line:
	free(line);
out_failure:
	return -1;
}