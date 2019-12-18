#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* serio; } ;
struct psmouse {char* vendor; char* name; TYPE_2__ ps2dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 scalar_t__ desired_serio_phys ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lifebook_dmi_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 

int lifebook_detect(struct psmouse *psmouse, bool set_properties)
{
        if (!dmi_check_system(lifebook_dmi_table))
                return -1;

	if (desired_serio_phys &&
	    strcmp(psmouse->ps2dev.serio->phys, desired_serio_phys))
		return -1;

	if (set_properties) {
		psmouse->vendor = "Fujitsu";
		psmouse->name = "Lifebook TouchScreen";
	}

        return 0;
}