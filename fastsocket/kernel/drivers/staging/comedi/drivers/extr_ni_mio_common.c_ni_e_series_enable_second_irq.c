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
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int reg_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  G0_Gate_Second_Irq_Enable ; 
 int /*<<< orphan*/  G1_Gate_Second_Irq_Enable ; 
 int /*<<< orphan*/  Second_IRQ_A_Enable_Register ; 
 int /*<<< orphan*/  Second_IRQ_B_Enable_Register ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 
 int ni_reg_m_series_mask ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_e_series_enable_second_irq(struct comedi_device *dev,
					  unsigned gpct_index, short enable)
{
	if (boardtype.reg_type & ni_reg_m_series_mask)
		return;
	switch (gpct_index) {
	case 0:
		if (enable) {
			devpriv->stc_writew(dev, G0_Gate_Second_Irq_Enable,
					    Second_IRQ_A_Enable_Register);
		} else {
			devpriv->stc_writew(dev, 0,
					    Second_IRQ_A_Enable_Register);
		}
		break;
	case 1:
		if (enable) {
			devpriv->stc_writew(dev, G1_Gate_Second_Irq_Enable,
					    Second_IRQ_B_Enable_Register);
		} else {
			devpriv->stc_writew(dev, 0,
					    Second_IRQ_B_Enable_Register);
		}
		break;
	default:
		BUG();
		break;
	}
}