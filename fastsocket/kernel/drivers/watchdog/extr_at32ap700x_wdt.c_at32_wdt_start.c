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
struct TYPE_3__ {int timeout; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EN ; 
 int /*<<< orphan*/  CTRL_KEY ; 
 int /*<<< orphan*/  CTRL_PSEL ; 
 int WDT_BF (int /*<<< orphan*/ ,int) ; 
 int WDT_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* wdt ; 
 int /*<<< orphan*/  wdt_writel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void at32_wdt_start(void)
{
	/* 0xf is 2^16 divider = 2 sec, 0xe is 2^15 divider = 1 sec */
	unsigned long psel = (wdt->timeout > 1) ? 0xf : 0xe;

	spin_lock(&wdt->io_lock);
	wdt_writel(wdt, CTRL, WDT_BIT(CTRL_EN)
			| WDT_BF(CTRL_PSEL, psel)
			| WDT_BF(CTRL_KEY, 0x55));
	wdt_writel(wdt, CTRL, WDT_BIT(CTRL_EN)
			| WDT_BF(CTRL_PSEL, psel)
			| WDT_BF(CTRL_KEY, 0xaa));
	spin_unlock(&wdt->io_lock);
}