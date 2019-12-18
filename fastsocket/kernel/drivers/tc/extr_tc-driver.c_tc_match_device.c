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
struct tc_driver {struct tc_device_id* id_table; } ;
struct tc_device_id {scalar_t__* vendor; scalar_t__* name; } ;
struct tc_dev {int /*<<< orphan*/  vendor; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__*) ; 

const struct tc_device_id *tc_match_device(struct tc_driver *tdrv,
					   struct tc_dev *tdev)
{
	const struct tc_device_id *id = tdrv->id_table;

	if (id) {
		while (id->name[0] || id->vendor[0]) {
			if (strcmp(tdev->name, id->name) == 0 &&
			    strcmp(tdev->vendor, id->vendor) == 0)
				return id;
			id++;
		}
	}
	return NULL;
}