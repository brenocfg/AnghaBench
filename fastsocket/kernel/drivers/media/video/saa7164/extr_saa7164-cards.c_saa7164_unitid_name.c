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
typedef  scalar_t__ u8 ;
struct saa7164_unit {scalar_t__ type; scalar_t__ id; char* name; } ;
struct saa7164_dev {size_t board; } ;
struct TYPE_2__ {struct saa7164_unit* unit; } ;

/* Variables and functions */
 int SAA7164_MAX_UNITS ; 
 scalar_t__ SAA7164_UNIT_UNDEFINED ; 
 TYPE_1__* saa7164_boards ; 

char *saa7164_unitid_name(struct saa7164_dev *dev, u8 unitid)
{
	char *undefed = "UNDEFINED";
	char *bridge = "BRIDGE";
	struct saa7164_unit *unit;
	int i;

	if (unitid == 0)
		return bridge;

	for (i = 0; i < SAA7164_MAX_UNITS; i++) {
		unit = &saa7164_boards[dev->board].unit[i];

		if (unit->type == SAA7164_UNIT_UNDEFINED)
			continue;

		if (unitid == unit->id)
				return unit->name;
	}

	return undefed;
}