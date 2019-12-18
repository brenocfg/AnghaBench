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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ appbase ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void msm_camio_vfe_blk_reset(void)
{
	uint32_t val;

	val = readl(appbase + 0x00000210);
	val |= 0x1;
	writel(val, appbase + 0x00000210);
	mdelay(10);

	val = readl(appbase + 0x00000210);
	val &= ~0x1;
	writel(val, appbase + 0x00000210);
	mdelay(10);
}