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
struct adbhid {scalar_t__ id; int flags; } ;

/* Variables and functions */
 scalar_t__ ADB_KEYBOARD ; 
 int FLAG_CAPSLOCK_IGNORE_NEXT ; 
 int FLAG_CAPSLOCK_TRANSLATE ; 
 struct adbhid** adbhid ; 

__attribute__((used)) static void
adbhid_kbd_capslock_remember(void)
{
	struct adbhid *ahid;
	int i;

	for (i = 1; i < 16; i++) {
		ahid = adbhid[i];

		if (ahid && ahid->id == ADB_KEYBOARD)
			if (ahid->flags & FLAG_CAPSLOCK_TRANSLATE)
				ahid->flags |= FLAG_CAPSLOCK_IGNORE_NEXT;
	}
}