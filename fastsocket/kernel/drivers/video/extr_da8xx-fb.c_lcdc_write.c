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
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 scalar_t__ da8xx_fb_reg_base ; 

__attribute__((used)) static inline void lcdc_write(unsigned int val, unsigned int addr)
{
	__raw_writel(val, da8xx_fb_reg_base + (addr));
}