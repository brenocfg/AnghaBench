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
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {int dummy; } ;
typedef  enum b43_dmatype { ____Placeholder_b43_dmatype } b43_dmatype ;

/* Variables and functions */
 int /*<<< orphan*/  b43_dmacontroller_base (int,unsigned int) ; 
 int /*<<< orphan*/  direct_fifo_rx (struct b43_wldev*,int,int /*<<< orphan*/ ,int) ; 
 int dma_mask_to_engine_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supported_dma_mask (struct b43_wldev*) ; 

void b43_dma_direct_fifo_rx(struct b43_wldev *dev,
			    unsigned int engine_index, bool enable)
{
	enum b43_dmatype type;
	u16 mmio_base;

	type = dma_mask_to_engine_type(supported_dma_mask(dev));

	mmio_base = b43_dmacontroller_base(type, engine_index);
	direct_fifo_rx(dev, type, mmio_base, enable);
}