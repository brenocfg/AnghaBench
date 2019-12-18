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
struct sys_device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ S3C24XX_EINFLT0 ; 
 scalar_t__ S3C24XX_EINTMASK ; 
 scalar_t__ S3C24XX_EXTINT0 ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * irq_save ; 
 int /*<<< orphan*/  s3c_pm_do_restore (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * save_eintflt ; 
 int /*<<< orphan*/  save_eintmask ; 
 int /*<<< orphan*/ * save_extint ; 

int s3c24xx_irq_resume(struct sys_device *dev)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(save_extint); i++)
		__raw_writel(save_extint[i], S3C24XX_EXTINT0 + (i*4));

	for (i = 0; i < ARRAY_SIZE(save_eintflt); i++)
		__raw_writel(save_eintflt[i], S3C24XX_EINFLT0 + (i*4));

	s3c_pm_do_restore(irq_save, ARRAY_SIZE(irq_save));
	__raw_writel(save_eintmask, S3C24XX_EINTMASK);

	return 0;
}