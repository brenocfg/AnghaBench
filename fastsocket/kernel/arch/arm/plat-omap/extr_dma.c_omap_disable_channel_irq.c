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
 int /*<<< orphan*/  CICR (int) ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 int /*<<< orphan*/  dma_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_disable_channel_irq(int lch)
{
	if (cpu_class_is_omap2())
		dma_write(0, CICR(lch));
}