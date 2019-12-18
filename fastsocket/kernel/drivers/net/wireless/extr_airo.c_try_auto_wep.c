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
struct airo_info {int flags; int /*<<< orphan*/  thr_wait; int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 int FLAG_RADIO_DOWN ; 
 int HZ ; 
 int /*<<< orphan*/  RUN_AT (int) ; 
 scalar_t__ auto_wep ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void try_auto_wep(struct airo_info *ai)
{
	if (auto_wep && !(ai->flags & FLAG_RADIO_DOWN)) {
		ai->expires = RUN_AT(3*HZ);
		wake_up_interruptible(&ai->thr_wait);
	}
}