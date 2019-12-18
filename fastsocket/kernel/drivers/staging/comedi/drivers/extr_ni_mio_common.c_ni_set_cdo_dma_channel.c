#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int cdio_dma_select_reg; int /*<<< orphan*/  soft_reg_copy_lock; } ;

/* Variables and functions */
 int CDO_DMA_Select_Mask ; 
 int CDO_DMA_Select_Shift ; 
 int /*<<< orphan*/  M_Offset_CDIO_DMA_Select ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  mmiowb () ; 
 int ni_stc_dma_channel_select_bitfield (int) ; 
 int /*<<< orphan*/  ni_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void ni_set_cdo_dma_channel(struct comedi_device *dev,
					  int mite_channel)
{
	unsigned long flags;

	spin_lock_irqsave(&devpriv->soft_reg_copy_lock, flags);
	devpriv->cdio_dma_select_reg &= ~CDO_DMA_Select_Mask;
	if (mite_channel >= 0) {
		/*XXX just guessing ni_stc_dma_channel_select_bitfield() returns the right bits,
		   under the assumption the cdio dma selection works just like ai/ao/gpct.
		   Definitely works for dma channels 0 and 1. */
		devpriv->cdio_dma_select_reg |=
		    (ni_stc_dma_channel_select_bitfield(mite_channel) <<
		     CDO_DMA_Select_Shift) & CDO_DMA_Select_Mask;
	}
	ni_writeb(devpriv->cdio_dma_select_reg, M_Offset_CDIO_DMA_Select);
	mmiowb();
	spin_unlock_irqrestore(&devpriv->soft_reg_copy_lock, flags);
}