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
typedef  int /*<<< orphan*/  lithium_t ;

/* Variables and functions */
 int /*<<< orphan*/  LI_HC_LINK_ENABLE ; 
 int /*<<< orphan*/  LI_HC_RESET ; 
 int /*<<< orphan*/  LI_HOST_CONTROLLER ; 
 int /*<<< orphan*/  li_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int li_init(lithium_t *lith)
{
	/* 1. System power supplies stabilize. */

	/* 2. Assert the ~RESET signal. */

	li_writel(lith, LI_HOST_CONTROLLER, LI_HC_RESET);
	udelay(1);

	/* 3. Deassert the ~RESET signal and enter a wait period to allow
	   the AD1843 internal clocks and the external crystal oscillator
	   to stabilize. */

	li_writel(lith, LI_HOST_CONTROLLER, LI_HC_LINK_ENABLE);
	udelay(1);

	return 0;
}