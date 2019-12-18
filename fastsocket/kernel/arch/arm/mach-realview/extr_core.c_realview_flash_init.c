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

/* Variables and functions */
 int /*<<< orphan*/  REALVIEW_FLASHCTRL ; 
 int /*<<< orphan*/  REALVIEW_FLASHPROG_FLVPPEN ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int realview_flash_init(void)
{
	u32 val;

	val = __raw_readl(REALVIEW_FLASHCTRL);
	val &= ~REALVIEW_FLASHPROG_FLVPPEN;
	__raw_writel(val, REALVIEW_FLASHCTRL);

	return 0;
}