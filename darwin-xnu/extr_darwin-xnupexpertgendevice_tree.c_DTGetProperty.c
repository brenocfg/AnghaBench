#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int nProperties; } ;
struct TYPE_6__ {unsigned int length; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ DeviceTreeNodeProperty ;
typedef  TYPE_2__* DTEntry ;

/* Variables and functions */
 int kError ; 
 int kSuccess ; 
 TYPE_1__* next_prop (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
DTGetProperty(const DTEntry entry, const char *propertyName, void **propertyValue, unsigned int *propertySize)
{
	DeviceTreeNodeProperty *prop;
	unsigned int k;

	if (entry == NULL || entry->nProperties == 0) {
		return kError;
	} else {
		prop = (DeviceTreeNodeProperty *) (entry + 1);
		for (k = 0; k < entry->nProperties; k++) {
			if (strcmp(prop->name, propertyName) == 0) {
				*propertyValue = (void *) (((uintptr_t)prop)
						+ sizeof(DeviceTreeNodeProperty));
				*propertySize = prop->length;
				return kSuccess;
			}
			prop = next_prop(prop);
		}
	}
	return kError;
}