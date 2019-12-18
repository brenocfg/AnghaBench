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
struct psmouse {char* vendor; char* name; } ;

/* Variables and functions */

__attribute__((used)) static int ps2bare_detect(struct psmouse *psmouse, bool set_properties)
{
	if (set_properties) {
		if (!psmouse->vendor) psmouse->vendor = "Generic";
		if (!psmouse->name) psmouse->name = "Mouse";
	}

	return 0;
}