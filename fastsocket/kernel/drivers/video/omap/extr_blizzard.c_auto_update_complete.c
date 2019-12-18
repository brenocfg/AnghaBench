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
struct TYPE_2__ {int /*<<< orphan*/  auto_update_timer; int /*<<< orphan*/  stop_auto_update; } ;

/* Variables and functions */
 scalar_t__ BLIZZARD_AUTO_UPDATE_TIME ; 
 TYPE_1__ blizzard ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void auto_update_complete(void *data)
{
	if (!blizzard.stop_auto_update)
		mod_timer(&blizzard.auto_update_timer,
			  jiffies + BLIZZARD_AUTO_UPDATE_TIME);
}