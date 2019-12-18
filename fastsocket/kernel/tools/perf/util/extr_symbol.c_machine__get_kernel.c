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
struct machine {int dummy; } ;
struct dso {int /*<<< orphan*/  has_build_id; } ;
typedef  int /*<<< orphan*/  bf ;
struct TYPE_2__ {char* vmlinux_name; char* default_guest_vmlinux_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_TYPE_GUEST_KERNEL ; 
 int /*<<< orphan*/  DSO_TYPE_KERNEL ; 
 int PATH_MAX ; 
 struct dso* dso__kernel_findnew (struct machine*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__read_running_kernel_build_id (struct dso*,struct machine*) ; 
 scalar_t__ machine__is_default_guest (struct machine*) ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 char* machine__mmap_name (struct machine*,char*,int) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static struct dso *machine__get_kernel(struct machine *machine)
{
	const char *vmlinux_name = NULL;
	struct dso *kernel;

	if (machine__is_host(machine)) {
		vmlinux_name = symbol_conf.vmlinux_name;
		if (!vmlinux_name)
			vmlinux_name = "[kernel.kallsyms]";

		kernel = dso__kernel_findnew(machine, vmlinux_name,
					     "[kernel]",
					     DSO_TYPE_KERNEL);
	} else {
		char bf[PATH_MAX];

		if (machine__is_default_guest(machine))
			vmlinux_name = symbol_conf.default_guest_vmlinux_name;
		if (!vmlinux_name)
			vmlinux_name = machine__mmap_name(machine, bf,
							  sizeof(bf));

		kernel = dso__kernel_findnew(machine, vmlinux_name,
					     "[guest.kernel]",
					     DSO_TYPE_GUEST_KERNEL);
	}

	if (kernel != NULL && (!kernel->has_build_id))
		dso__read_running_kernel_build_id(kernel, machine);

	return kernel;
}