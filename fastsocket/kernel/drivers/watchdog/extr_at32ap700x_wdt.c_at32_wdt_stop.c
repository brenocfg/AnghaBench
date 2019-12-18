#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_KEY ; 
 int /*<<< orphan*/  CTRL_PSEL ; 
 unsigned long WDT_BF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* wdt ; 
 unsigned long wdt_readl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_writel (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void at32_wdt_stop(void)
{
	unsigned long psel;

	spin_lock(&wdt->io_lock);
	psel = wdt_readl(wdt, CTRL) & WDT_BF(CTRL_PSEL, 0x0f);
	wdt_writel(wdt, CTRL, psel | WDT_BF(CTRL_KEY, 0x55));
	wdt_writel(wdt, CTRL, psel | WDT_BF(CTRL_KEY, 0xaa));
	spin_unlock(&wdt->io_lock);
}