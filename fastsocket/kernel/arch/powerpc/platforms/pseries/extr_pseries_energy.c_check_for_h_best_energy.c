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
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_path (char*) ; 
 char* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static int check_for_h_best_energy(void)
{
	struct device_node *rtas = NULL;
	const char *hypertas, *s;
	int length;
	int rc = 0;

	rtas = of_find_node_by_path("/rtas");
	if (!rtas)
		return 0;

	hypertas = of_get_property(rtas, "ibm,hypertas-functions", &length);
	if (!hypertas) {
		of_node_put(rtas);
		return 0;
	}

	/* hypertas will have list of strings with hcall names */
	for (s = hypertas; s < hypertas + length; s += strlen(s) + 1) {
		if (!strncmp("hcall-best-energy-1", s, 19)) {
			rc = 1; /* Found the string */
			break;
		}
	}
	of_node_put(rtas);
	return rc;
}