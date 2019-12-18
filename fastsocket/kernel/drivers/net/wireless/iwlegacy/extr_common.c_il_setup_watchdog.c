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
struct il_priv {int /*<<< orphan*/  watchdog; TYPE_1__* cfg; } ;
struct TYPE_2__ {unsigned int wd_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_WD_TICK (unsigned int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void
il_setup_watchdog(struct il_priv *il)
{
	unsigned int timeout = il->cfg->wd_timeout;

	if (timeout)
		mod_timer(&il->watchdog,
			  jiffies + msecs_to_jiffies(IL_WD_TICK(timeout)));
	else
		del_timer(&il->watchdog);
}