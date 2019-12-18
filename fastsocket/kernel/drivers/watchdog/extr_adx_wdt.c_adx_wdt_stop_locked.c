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
typedef  int /*<<< orphan*/  u32 ;
struct adx_wdt {int /*<<< orphan*/  state; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ADX_WDT_CONTROL ; 
 int /*<<< orphan*/  ADX_WDT_CONTROL_ENABLE ; 
 int /*<<< orphan*/  WDT_STATE_STOP ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void adx_wdt_stop_locked(struct adx_wdt *wdt)
{
	u32 ctrl;

	ctrl = readl(wdt->base + ADX_WDT_CONTROL);
	ctrl &= ~ADX_WDT_CONTROL_ENABLE;
	writel(ctrl, wdt->base + ADX_WDT_CONTROL);
	wdt->state = WDT_STATE_STOP;
}