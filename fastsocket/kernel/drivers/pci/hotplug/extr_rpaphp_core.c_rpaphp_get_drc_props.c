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
struct device_node {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int get_children_props (int /*<<< orphan*/ ,int const**,int const**,int const**,int const**) ; 
 unsigned int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

int rpaphp_get_drc_props(struct device_node *dn, int *drc_index,
		char **drc_name, char **drc_type, int *drc_power_domain)
{
	const int *indexes, *names;
	const int *types, *domains;
	const unsigned int *my_index;
	char *name_tmp, *type_tmp;
	int i, rc;

	my_index = of_get_property(dn, "ibm,my-drc-index", NULL);
	if (!my_index) {
		/* Node isn't DLPAR/hotplug capable */
		return -EINVAL;
	}

	rc = get_children_props(dn->parent, &indexes, &names, &types, &domains);
	if (rc < 0) {
		return -EINVAL;
	}

	name_tmp = (char *) &names[1];
	type_tmp = (char *) &types[1];

	/* Iterate through parent properties, looking for my-drc-index */
	for (i = 0; i < indexes[0]; i++) {
		if ((unsigned int) indexes[i + 1] == *my_index) {
			if (drc_name)
                		*drc_name = name_tmp;
			if (drc_type)
				*drc_type = type_tmp;
			if (drc_index)
				*drc_index = *my_index;
			if (drc_power_domain)
				*drc_power_domain = domains[i+1];
			return 0;
		}
		name_tmp += (strlen(name_tmp) + 1);
		type_tmp += (strlen(type_tmp) + 1);
	}

	return -EINVAL;
}