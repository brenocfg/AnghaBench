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

/* Variables and functions */
 unsigned long S3C64XX_PWRCFG_CFG_WFI_MASK ; 
 unsigned long S3C64XX_PWRCFG_CFG_WFI_SLEEP ; 
 int /*<<< orphan*/  S3C64XX_PWR_CFG ; 
 int /*<<< orphan*/  S3C64XX_WAKEUP_STAT ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  s3c_pm_debug_smdkled (int,int) ; 

__attribute__((used)) static void s3c64xx_cpu_suspend(void)
{
	unsigned long tmp;

	/* set our standby method to sleep */

	tmp = __raw_readl(S3C64XX_PWR_CFG);
	tmp &= ~S3C64XX_PWRCFG_CFG_WFI_MASK;
	tmp |= S3C64XX_PWRCFG_CFG_WFI_SLEEP;
	__raw_writel(tmp, S3C64XX_PWR_CFG);

	/* clear any old wakeup */

	__raw_writel(__raw_readl(S3C64XX_WAKEUP_STAT),
		     S3C64XX_WAKEUP_STAT);

	/* set the LED state to 0110 over sleep */
	s3c_pm_debug_smdkled(3 << 1, 0xf);

	/* issue the standby signal into the pm unit. Note, we
	 * issue a write-buffer drain just in case */

	tmp = 0;

	asm("b 1f\n\t"
	    ".align 5\n\t"
	    "1:\n\t"
	    "mcr p15, 0, %0, c7, c10, 5\n\t"
	    "mcr p15, 0, %0, c7, c10, 4\n\t"
	    "mcr p15, 0, %0, c7, c0, 4" :: "r" (tmp));

	/* we should never get past here */

	panic("sleep resumed to originator?");
}