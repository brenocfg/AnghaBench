#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int nProperties; } ;
typedef  TYPE_1__* RealDTEntry ;
typedef  int /*<<< orphan*/  DeviceTreeNodeProperty ;

/* Variables and functions */
 int /*<<< orphan*/ * next_prop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RealDTEntry
skipProperties(RealDTEntry entry)
{
	DeviceTreeNodeProperty *prop;
	unsigned int k;

	if (entry == NULL || entry->nProperties == 0) {
		return NULL;
	} else {
		prop = (DeviceTreeNodeProperty *) (entry + 1);
		for (k = 0; k < entry->nProperties; k++) {
			prop = next_prop(prop);
		}
	}
	return ((RealDTEntry) prop);
}