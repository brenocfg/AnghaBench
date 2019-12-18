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
struct property {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int NOTIFY_BAD ; 
 int PSERIES_DRCONF_MEM_ADD ; 
 int PSERIES_DRCONF_MEM_REMOVE ; 
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,int,unsigned char*) ; 
 struct property* new_property (char*,int,unsigned char*,int /*<<< orphan*/ *) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pSeries_reconfig_chain ; 
 char* parse_next_property (char*,char*,char**,int*,unsigned char**) ; 
 char* parse_node (char*,size_t,struct device_node**) ; 
 int prom_add_property (struct device_node*,struct property*) ; 
 int prom_update_property (struct device_node*,struct property*,struct property*) ; 
 int /*<<< orphan*/  slb_set_size (int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int do_update_property(char *buf, size_t bufsize)
{
	struct device_node *np;
	unsigned char *value;
	char *name, *end, *next_prop;
	int rc, length;
	struct property *newprop, *oldprop;
	buf = parse_node(buf, bufsize, &np);
	end = buf + bufsize;

	if (!np)
		return -ENODEV;

	next_prop = parse_next_property(buf, end, &name, &length, &value);
	if (!next_prop)
		return -EINVAL;

	newprop = new_property(name, length, value, NULL);
	if (!newprop)
		return -ENOMEM;

	if (!strcmp(name, "slb-size") || !strcmp(name, "ibm,slb-size"))
		slb_set_size(*(int *)value);

	oldprop = of_find_property(np, name,NULL);
	if (!oldprop) {
		if (strlen(name))
			return prom_add_property(np, newprop);
		return -ENODEV;
	}

	rc = prom_update_property(np, newprop, oldprop);
	if (rc)
		return rc;

	/* For memory under the ibm,dynamic-reconfiguration-memory node
	 * of the device tree, adding and removing memory is just an update
	 * to the ibm,dynamic-memory property instead of adding/removing a
	 * memory node in the device tree.  For these cases we still need to
	 * involve the notifier chain.
	 */
	if (!strcmp(name, "ibm,dynamic-memory")) {
		int action;

		next_prop = parse_next_property(next_prop, end, &name,
						&length, &value);
		if (!next_prop)
			return -EINVAL;

		if (!strcmp(name, "add"))
			action = PSERIES_DRCONF_MEM_ADD;
		else
			action = PSERIES_DRCONF_MEM_REMOVE;

		rc = blocking_notifier_call_chain(&pSeries_reconfig_chain,
						  action, value);
		if (rc == NOTIFY_BAD) {
			rc = prom_update_property(np, oldprop, newprop);
			return -ENOMEM;
		}
	}

	return 0;
}