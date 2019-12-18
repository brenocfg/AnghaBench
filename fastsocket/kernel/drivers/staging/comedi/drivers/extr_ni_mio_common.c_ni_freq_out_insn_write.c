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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clock_and_fout; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Clock_and_FOUT_Register ; 
 int /*<<< orphan*/  FOUT_Divider (unsigned int) ; 
 int /*<<< orphan*/  FOUT_Divider_mask ; 
 int /*<<< orphan*/  FOUT_Enable ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_freq_out_insn_write(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn, unsigned int *data)
{
	devpriv->clock_and_fout &= ~FOUT_Enable;
	devpriv->stc_writew(dev, devpriv->clock_and_fout,
			    Clock_and_FOUT_Register);
	devpriv->clock_and_fout &= ~FOUT_Divider_mask;
	devpriv->clock_and_fout |= FOUT_Divider(data[0]);
	devpriv->clock_and_fout |= FOUT_Enable;
	devpriv->stc_writew(dev, devpriv->clock_and_fout,
			    Clock_and_FOUT_Register);
	return insn->n;
}