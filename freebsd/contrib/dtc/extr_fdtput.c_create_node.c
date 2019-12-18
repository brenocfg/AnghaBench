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
 int FDT_ERR_BADPATH ; 
 int fdt_add_subnode (char*,int,char*) ; 
 int fdt_path_offset (char*,char const*) ; 
 char* realloc_node (char*,char*) ; 
 int /*<<< orphan*/  report_error (char const*,int,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int create_node(char **blob, const char *node_name)
{
	int node = 0;
	char *p;

	p = strrchr(node_name, '/');
	if (!p) {
		report_error(node_name, -1, -FDT_ERR_BADPATH);
		return -1;
	}
	*p = '\0';

	*blob = realloc_node(*blob, p + 1);

	if (p > node_name) {
		node = fdt_path_offset(*blob, node_name);
		if (node < 0) {
			report_error(node_name, -1, node);
			return -1;
		}
	}

	node = fdt_add_subnode(*blob, node, p + 1);
	if (node < 0) {
		report_error(p + 1, -1, node);
		return -1;
	}

	return 0;
}