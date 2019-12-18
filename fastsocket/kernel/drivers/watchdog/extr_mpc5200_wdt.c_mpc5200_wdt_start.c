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
struct mpc5200_wdt {int count; int /*<<< orphan*/  io_lock; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int GPT_MODE_CE ; 
 int GPT_MODE_MS_TIMER ; 
 int GPT_MODE_WDT ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpc5200_wdt_start(struct mpc5200_wdt *wdt)
{
	spin_lock(&wdt->io_lock);
	/* disable */
	out_be32(&wdt->regs->mode, 0);
	/* set timeout, with maximum prescaler */
	out_be32(&wdt->regs->count, 0x0 | wdt->count);
	/* enable watchdog */
	out_be32(&wdt->regs->mode, GPT_MODE_CE | GPT_MODE_WDT |
						GPT_MODE_MS_TIMER);
	spin_unlock(&wdt->io_lock);

	return 0;
}