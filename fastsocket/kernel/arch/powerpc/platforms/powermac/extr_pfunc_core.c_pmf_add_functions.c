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
struct property {char* name; int length; int /*<<< orphan*/  value; struct property* next; } ;
struct pmf_device {TYPE_1__* node; } ;
struct TYPE_2__ {struct property* properties; } ;

/* Variables and functions */
 char* PP_PREFIX ; 
 scalar_t__ pmf_add_function_prop (struct pmf_device*,void*,char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int const) ; 

__attribute__((used)) static int pmf_add_functions(struct pmf_device *dev, void *driverdata)
{
	struct property *pp;
#define PP_PREFIX "platform-do-"
	const int plen = strlen(PP_PREFIX);
	int count = 0;

	for (pp = dev->node->properties; pp != 0; pp = pp->next) {
		char *name;
		if (strncmp(pp->name, PP_PREFIX, plen) != 0)
			continue;
		name = pp->name + plen;
		if (strlen(name) && pp->length >= 12)
			count += pmf_add_function_prop(dev, driverdata, name,
						       pp->value, pp->length);
	}
	return count;
}