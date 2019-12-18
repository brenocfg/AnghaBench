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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {TYPE_1__* hba_bus; } ;
struct lba_device {TYPE_2__ hba; } ;
struct TYPE_3__ {scalar_t__ secondary; scalar_t__ subordinate; } ;

/* Variables and functions */
 scalar_t__ LBA_MAX_NUM_BUSES ; 

__attribute__((used)) static int lba_device_present(u8 bus, u8 dfn, struct lba_device *d)
{
	u8 first_bus = d->hba.hba_bus->secondary;
	u8 last_sub_bus = d->hba.hba_bus->subordinate;

	if ((bus < first_bus) ||
	    (bus > last_sub_bus) ||
	    ((bus - first_bus) >= LBA_MAX_NUM_BUSES)) {
		return 0;
	}

	return 1;
}