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
typedef  int u32 ;
typedef  enum omap_dma_write_mode { ____Placeholder_omap_dma_write_mode } omap_dma_write_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CSDP (int) ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 

void omap_set_dma_write_mode(int lch, enum omap_dma_write_mode mode)
{
	if (cpu_class_is_omap2()) {
		u32 csdp;

		csdp = dma_read(CSDP(lch));
		csdp &= ~(0x3 << 16);
		csdp |= (mode << 16);
		dma_write(csdp, CSDP(lch));
	}
}