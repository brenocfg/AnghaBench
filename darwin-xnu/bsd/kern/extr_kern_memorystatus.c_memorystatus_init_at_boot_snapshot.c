#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  snapshot_time; scalar_t__ notification_time; scalar_t__ entry_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  mach_absolute_time () ; 
 TYPE_1__ memorystatus_at_boot_snapshot ; 
 int /*<<< orphan*/  memorystatus_init_snapshot_vmstats (TYPE_1__*) ; 

void
memorystatus_init_at_boot_snapshot() {
	memorystatus_init_snapshot_vmstats(&memorystatus_at_boot_snapshot);
	memorystatus_at_boot_snapshot.entry_count = 0;
	memorystatus_at_boot_snapshot.notification_time = 0;   /* updated when consumed */
	memorystatus_at_boot_snapshot.snapshot_time = mach_absolute_time();
}