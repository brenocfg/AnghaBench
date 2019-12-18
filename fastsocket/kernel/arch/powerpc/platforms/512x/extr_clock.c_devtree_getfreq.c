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
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 unsigned int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static unsigned long devtree_getfreq(char *clockname)
{
	struct device_node *np;
	const unsigned int *prop;
	unsigned int val = 0;

	np = of_find_compatible_node(NULL, NULL, "fsl,mpc5121-immr");
	if (np) {
		prop = of_get_property(np, clockname, NULL);
		if (prop)
			val = *prop;
	    of_node_put(np);
	}
	return val;
}