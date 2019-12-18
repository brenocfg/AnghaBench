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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CCR (int) ; 
#define  OMAP_DMA_PORT_EMIFF 131 
#define  OMAP_DMA_PORT_EMIFS 130 
#define  OMAP_DMA_PORT_OCP_T1 129 
#define  OMAP_DMA_PORT_OCP_T2 128 
 unsigned long OMAP_TC_EMIFF_PRIOR ; 
 unsigned long OMAP_TC_EMIFS_PRIOR ; 
 unsigned long OMAP_TC_OCPT1_PRIOR ; 
 unsigned long OMAP_TC_OCPT2_PRIOR ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 
 int omap_readl (unsigned long) ; 
 int /*<<< orphan*/  omap_writel (int,unsigned long) ; 

void omap_set_dma_priority(int lch, int dst_port, int priority)
{
	unsigned long reg;
	u32 l;

	if (cpu_class_is_omap1()) {
		switch (dst_port) {
		case OMAP_DMA_PORT_OCP_T1:	/* FFFECC00 */
			reg = OMAP_TC_OCPT1_PRIOR;
			break;
		case OMAP_DMA_PORT_OCP_T2:	/* FFFECCD0 */
			reg = OMAP_TC_OCPT2_PRIOR;
			break;
		case OMAP_DMA_PORT_EMIFF:	/* FFFECC08 */
			reg = OMAP_TC_EMIFF_PRIOR;
			break;
		case OMAP_DMA_PORT_EMIFS:	/* FFFECC04 */
			reg = OMAP_TC_EMIFS_PRIOR;
			break;
		default:
			BUG();
			return;
		}
		l = omap_readl(reg);
		l &= ~(0xf << 8);
		l |= (priority & 0xf) << 8;
		omap_writel(l, reg);
	}

	if (cpu_class_is_omap2()) {
		u32 ccr;

		ccr = dma_read(CCR(lch));
		if (priority)
			ccr |= (1 << 6);
		else
			ccr &= ~(1 << 6);
		dma_write(ccr, CCR(lch));
	}
}