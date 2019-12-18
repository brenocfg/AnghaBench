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
 scalar_t__ OMAP1_32K_TIMER_BASE ; 
 int omap_readl (scalar_t__) ; 

__attribute__((used)) static inline unsigned long omap_32k_timer_read(int reg)
{
	return omap_readl(OMAP1_32K_TIMER_BASE + reg) & 0xffffff;
}