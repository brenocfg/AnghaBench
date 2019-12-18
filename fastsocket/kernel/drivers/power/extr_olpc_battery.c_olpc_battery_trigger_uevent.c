#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* dev; } ;
struct TYPE_7__ {TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 unsigned long EC_SCI_SRC_ACPWR ; 
 unsigned long EC_SCI_SRC_BATERR ; 
 unsigned long EC_SCI_SRC_BATSOC ; 
 unsigned long EC_SCI_SRC_BATTERY ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ olpc_ac ; 
 TYPE_3__ olpc_bat ; 

void olpc_battery_trigger_uevent(unsigned long cause)
{
	if (cause & EC_SCI_SRC_ACPWR)
		kobject_uevent(&olpc_ac.dev->kobj, KOBJ_CHANGE);
	if (cause & (EC_SCI_SRC_BATERR|EC_SCI_SRC_BATSOC|EC_SCI_SRC_BATTERY))
		kobject_uevent(&olpc_bat.dev->kobj, KOBJ_CHANGE);
}