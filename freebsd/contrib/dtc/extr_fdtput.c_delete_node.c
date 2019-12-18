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
 int fdt_del_node (char*,int) ; 
 int fdt_path_offset (char*,char const*) ; 
 int /*<<< orphan*/  report_error (char const*,int,int) ; 

__attribute__((used)) static int delete_node(char *blob, const char *node_name)
{
	int node = 0;

	node = fdt_path_offset(blob, node_name);
	if (node < 0) {
		report_error(node_name, -1, node);
		return -1;
	}

	node = fdt_del_node(blob, node);
	if (node < 0) {
		report_error(node_name, -1, node);
		return -1;
	}

	return 0;
}