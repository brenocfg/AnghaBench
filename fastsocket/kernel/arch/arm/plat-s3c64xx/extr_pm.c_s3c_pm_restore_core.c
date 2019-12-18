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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C64XX_EINT_MASK ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_save ; 
 int /*<<< orphan*/  misc_save ; 
 int /*<<< orphan*/  s3c_pm_debug_smdkled (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_pm_do_restore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_pm_do_restore_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void s3c_pm_restore_core(void)
{
	__raw_writel(0, S3C64XX_EINT_MASK);

	s3c_pm_debug_smdkled(1 << 2, 0);

	s3c_pm_do_restore_core(core_save, ARRAY_SIZE(core_save));
	s3c_pm_do_restore(misc_save, ARRAY_SIZE(misc_save));
}