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
struct map {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int __show_available_funcs (struct map*) ; 
 int init_vmlinux () ; 
 struct map* kernel_get_module_map (char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 

__attribute__((used)) static int available_kernel_funcs(const char *module)
{
	struct map *map;
	int ret;

	ret = init_vmlinux();
	if (ret < 0)
		return ret;

	map = kernel_get_module_map(module);
	if (!map) {
		pr_err("Failed to find %s map.\n", (module) ? : "kernel");
		return -EINVAL;
	}
	return __show_available_funcs(map);
}