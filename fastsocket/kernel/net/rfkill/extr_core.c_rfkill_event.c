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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct rfkill {TYPE_1__ dev; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  RFKILL_OP_CHANGE ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_send_events (struct rfkill*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfkill_event(struct rfkill *rfkill)
{
	if (!rfkill->registered)
		return;

	kobject_uevent(&rfkill->dev.kobj, KOBJ_CHANGE);

	/* also send event to /dev/rfkill */
	rfkill_send_events(rfkill, RFKILL_OP_CHANGE);
}