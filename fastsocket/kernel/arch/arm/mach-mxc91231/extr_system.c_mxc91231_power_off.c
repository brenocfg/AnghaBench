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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  WDOG_WCR ; 
 int /*<<< orphan*/  WDOG_WCR_ASSERT ; 
 int /*<<< orphan*/  WDOG_WCR_OUT_ENABLE ; 
 int /*<<< orphan*/  __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mxc91231_power_off(void)
{
	u16 wcr;

	wcr = __raw_readw(WDOG_WCR);
	wcr |= WDOG_WCR_OUT_ENABLE;
	wcr &= ~WDOG_WCR_ASSERT;
	__raw_writew(wcr, WDOG_WCR);
}