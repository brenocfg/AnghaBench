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
struct usbmix_selector_map {int id; int count; int /*<<< orphan*/ * names; } ;
struct mixer_build {struct usbmix_selector_map* selector_map; } ;

/* Variables and functions */
 int strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_mapped_selector_name(struct mixer_build *state, int unitid,
				      int index, char *buf, int buflen)
{
	const struct usbmix_selector_map *p;

	if (! state->selector_map)
		return 0;
	for (p = state->selector_map; p->id; p++) {
		if (p->id == unitid && index < p->count)
			return strlcpy(buf, p->names[index], buflen);
	}
	return 0;
}