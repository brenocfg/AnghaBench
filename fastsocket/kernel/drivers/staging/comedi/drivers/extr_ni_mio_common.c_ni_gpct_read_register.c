#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ni_gpct {TYPE_1__* counter_dev; } ;
struct comedi_device {int dummy; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;
struct TYPE_4__ {int (* stc_readl ) (struct comedi_device*,unsigned int) ;int (* stc_readw ) (struct comedi_device*,unsigned int) ;} ;
struct TYPE_3__ {struct comedi_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_Offset_G0_DMA_Status ; 
 int /*<<< orphan*/  M_Offset_G1_DMA_Status ; 
#define  NITIO_G0_DMA_Status_Reg 133 
#define  NITIO_G0_HW_Save_Reg 132 
#define  NITIO_G0_SW_Save_Reg 131 
#define  NITIO_G1_DMA_Status_Reg 130 
#define  NITIO_G1_HW_Save_Reg 129 
#define  NITIO_G1_SW_Save_Reg 128 
 TYPE_2__* devpriv ; 
 unsigned int ni_gpct_to_stc_register (int) ; 
 int ni_readw (int /*<<< orphan*/ ) ; 
 int stub1 (struct comedi_device*,unsigned int) ; 
 int stub2 (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static unsigned ni_gpct_read_register(struct ni_gpct *counter,
				      enum ni_gpct_register reg)
{
	struct comedi_device *dev = counter->counter_dev->dev;
	unsigned stc_register;
	switch (reg) {
		/* m-series only registers */
	case NITIO_G0_DMA_Status_Reg:
		return ni_readw(M_Offset_G0_DMA_Status);
		break;
	case NITIO_G1_DMA_Status_Reg:
		return ni_readw(M_Offset_G1_DMA_Status);
		break;

		/* 32 bit registers */
	case NITIO_G0_HW_Save_Reg:
	case NITIO_G1_HW_Save_Reg:
	case NITIO_G0_SW_Save_Reg:
	case NITIO_G1_SW_Save_Reg:
		stc_register = ni_gpct_to_stc_register(reg);
		return devpriv->stc_readl(dev, stc_register);
		break;

		/* 16 bit registers */
	default:
		stc_register = ni_gpct_to_stc_register(reg);
		return devpriv->stc_readw(dev, stc_register);
		break;
	}
	return 0;
}