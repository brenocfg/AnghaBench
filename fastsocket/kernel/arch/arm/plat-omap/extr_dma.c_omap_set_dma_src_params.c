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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CCR (int) ; 
 int /*<<< orphan*/  CSDP (int) ; 
 int /*<<< orphan*/  CSEI (int) ; 
 int /*<<< orphan*/  CSFI (int) ; 
 int /*<<< orphan*/  CSSA (int) ; 
 int /*<<< orphan*/  CSSA_L (int) ; 
 int /*<<< orphan*/  CSSA_U (int) ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 

void omap_set_dma_src_params(int lch, int src_port, int src_amode,
			     unsigned long src_start,
			     int src_ei, int src_fi)
{
	u32 l;

	if (cpu_class_is_omap1()) {
		u16 w;

		w = dma_read(CSDP(lch));
		w &= ~(0x1f << 2);
		w |= src_port << 2;
		dma_write(w, CSDP(lch));
	}

	l = dma_read(CCR(lch));
	l &= ~(0x03 << 12);
	l |= src_amode << 12;
	dma_write(l, CCR(lch));

	if (cpu_class_is_omap1()) {
		dma_write(src_start >> 16, CSSA_U(lch));
		dma_write((u16)src_start, CSSA_L(lch));
	}

	if (cpu_class_is_omap2())
		dma_write(src_start, CSSA(lch));

	dma_write(src_ei, CSEI(lch));
	dma_write(src_fi, CSFI(lch));
}