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
 int /*<<< orphan*/  clk_add_alias (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nokia770_hwa742_platform_data ; 
 int /*<<< orphan*/  omapfb_set_ctrl_platform_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hwa742_dev_init(void)
{
	clk_add_alias("hwa_sys_ck", NULL, "bclk", NULL);
	omapfb_set_ctrl_platform_data(&nokia770_hwa742_platform_data);
}