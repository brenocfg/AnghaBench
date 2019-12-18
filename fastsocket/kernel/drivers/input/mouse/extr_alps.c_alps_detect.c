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
struct psmouse {char* vendor; char* name; int model; } ;
struct alps_data {int flags; int proto_version; } ;

/* Variables and functions */
 int ALPS_DUALPOINT ; 
 scalar_t__ alps_identify (struct psmouse*,struct alps_data*) ; 

int alps_detect(struct psmouse *psmouse, bool set_properties)
{
	struct alps_data dummy;

	if (alps_identify(psmouse, &dummy) < 0)
		return -1;

	if (set_properties) {
		psmouse->vendor = "ALPS";
		psmouse->name = dummy.flags & ALPS_DUALPOINT ?
				"DualPoint TouchPad" : "GlidePoint";
		psmouse->model = dummy.proto_version << 8;
	}
	return 0;
}