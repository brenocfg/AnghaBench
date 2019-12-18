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

/* Variables and functions */
 int FDT_ERR_NOSPACE ; 
 int fdt_path_offset (char*,char const*) ; 
 int fdt_setprop (char*,int,char const*,char const*,int) ; 
 char* realloc_property (char*,int,char const*,int) ; 
 int /*<<< orphan*/  report_error (char const*,int,int) ; 

__attribute__((used)) static int store_key_value(char **blob, const char *node_name,
		const char *property, const char *buf, int len)
{
	int node;
	int err;

	node = fdt_path_offset(*blob, node_name);
	if (node < 0) {
		report_error(node_name, -1, node);
		return -1;
	}

	err = fdt_setprop(*blob, node, property, buf, len);
	if (err == -FDT_ERR_NOSPACE) {
		*blob = realloc_property(*blob, node, property, len);
		err = fdt_setprop(*blob, node, property, buf, len);
	}
	if (err) {
		report_error(property, -1, err);
		return -1;
	}
	return 0;
}