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
typedef  int /*<<< orphan*/  symbol_filter_t ;
struct map {int dummy; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 char* dso__build_id_filename (struct dso*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dso__load_vmlinux (struct dso*,struct map*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__set_long_name (struct dso*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char** vmlinux_path ; 
 int vmlinux_path__nr_entries ; 

int dso__load_vmlinux_path(struct dso *dso, struct map *map,
			   symbol_filter_t filter)
{
	int i, err = 0;
	char *filename;

	pr_debug("Looking at the vmlinux_path (%d entries long)\n",
		 vmlinux_path__nr_entries + 1);

	filename = dso__build_id_filename(dso, NULL, 0);
	if (filename != NULL) {
		err = dso__load_vmlinux(dso, map, filename, filter);
		if (err > 0)
			goto out;
		free(filename);
	}

	for (i = 0; i < vmlinux_path__nr_entries; ++i) {
		err = dso__load_vmlinux(dso, map, vmlinux_path[i], filter);
		if (err > 0) {
			dso__set_long_name(dso, strdup(vmlinux_path[i]));
			break;
		}
	}
out:
	return err;
}