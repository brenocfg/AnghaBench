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
struct TYPE_2__ {int /*<<< orphan*/  ws_do_table_event; } ;
struct raid_set {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearRSScBusy (struct raid_set*) ; 
 int /*<<< orphan*/  TestSetRSScBusy (struct raid_set*) ; 
 scalar_t__ sc_busy (struct raid_set*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_busy_event(struct raid_set *rs)
{
	if (sc_busy(rs)) {
		if (!TestSetRSScBusy(rs))
			schedule_work(&rs->io.ws_do_table_event);
	} else
		ClearRSScBusy(rs);
}