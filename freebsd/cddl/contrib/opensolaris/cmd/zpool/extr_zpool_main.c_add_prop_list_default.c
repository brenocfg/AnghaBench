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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int add_prop_list (char const*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char const*,char**) ; 

__attribute__((used)) static int
add_prop_list_default(const char *propname, char *propval, nvlist_t **props,
    boolean_t poolprop)
{
	char *pval;

	if (nvlist_lookup_string(*props, propname, &pval) == 0)
		return (0);

	return (add_prop_list(propname, propval, props, poolprop));
}