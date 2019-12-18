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
struct usbmix_name_map {int id; int control; } ;
struct mixer_build {struct usbmix_name_map* map; } ;

/* Variables and functions */

__attribute__((used)) static const struct usbmix_name_map *
find_map(struct mixer_build *state, int unitid, int control)
{
	const struct usbmix_name_map *p = state->map;

	if (!p)
		return NULL;

	for (p = state->map; p->id; p++) {
		if (p->id == unitid &&
		    (!control || !p->control || control == p->control))
			return p;
	}
	return NULL;
}