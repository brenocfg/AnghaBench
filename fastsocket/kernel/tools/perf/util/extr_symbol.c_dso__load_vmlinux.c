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
typedef  int /*<<< orphan*/  symfs_vmlinux ;
typedef  int /*<<< orphan*/  symbol_filter_t ;
struct symsrc {int dummy; } ;
struct map {int /*<<< orphan*/  type; } ;
struct dso {scalar_t__ kernel; } ;
typedef  enum dso_binary_type { ____Placeholder_dso_binary_type } dso_binary_type ;
struct TYPE_2__ {char* symfs; } ;

/* Variables and functions */
 int DSO_BINARY_TYPE__GUEST_VMLINUX ; 
 int DSO_BINARY_TYPE__VMLINUX ; 
 scalar_t__ DSO_TYPE_GUEST_KERNEL ; 
 int PATH_MAX ; 
 int dso__load_sym (struct dso*,struct map*,struct symsrc*,struct symsrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__set_loaded (struct dso*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__set_long_name (struct dso*,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  symsrc__destroy (struct symsrc*) ; 
 scalar_t__ symsrc__init (struct symsrc*,struct dso*,char*,int) ; 

int dso__load_vmlinux(struct dso *dso, struct map *map,
		      const char *vmlinux, symbol_filter_t filter)
{
	int err = -1;
	struct symsrc ss;
	char symfs_vmlinux[PATH_MAX];
	enum dso_binary_type symtab_type;

	snprintf(symfs_vmlinux, sizeof(symfs_vmlinux), "%s%s",
		 symbol_conf.symfs, vmlinux);

	if (dso->kernel == DSO_TYPE_GUEST_KERNEL)
		symtab_type = DSO_BINARY_TYPE__GUEST_VMLINUX;
	else
		symtab_type = DSO_BINARY_TYPE__VMLINUX;

	if (symsrc__init(&ss, dso, symfs_vmlinux, symtab_type))
		return -1;

	err = dso__load_sym(dso, map, &ss, &ss, filter, 0);
	symsrc__destroy(&ss);

	if (err > 0) {
		dso__set_long_name(dso, (char *)vmlinux);
		dso__set_loaded(dso, map->type);
		pr_debug("Using %s for symbols\n", symfs_vmlinux);
	}

	return err;
}