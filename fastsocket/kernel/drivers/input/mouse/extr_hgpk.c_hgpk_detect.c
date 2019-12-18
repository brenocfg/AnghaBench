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

/* Variables and functions */
 int hgpk_get_model (struct psmouse*) ; 

int hgpk_detect(struct psmouse *psmouse, bool set_properties)
{
	int version;

	version = hgpk_get_model(psmouse);
	if (version < 0)
		return version;

	if (set_properties) {
		psmouse->vendor = "ALPS";
		psmouse->name = "HGPK";
		psmouse->model = version;
	}

	return 0;
}