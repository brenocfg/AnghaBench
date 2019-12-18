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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int reg_type; } ;
struct TYPE_3__ {unsigned int* ao; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAC0_Direct_Data ; 
 int /*<<< orphan*/  DAC1_Direct_Data ; 
 int /*<<< orphan*/  M_Offset_DAC_Direct_Data (unsigned int) ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 
 unsigned int ni_ao_config_chanlist (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ni_reg_m_series_mask ; 
 int /*<<< orphan*/  ni_writew (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ao_insn_write(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int invert;

	invert = ni_ao_config_chanlist(dev, s, &insn->chanspec, 1, 0);

	devpriv->ao[chan] = data[0];

	if (boardtype.reg_type & ni_reg_m_series_mask) {
		ni_writew(data[0], M_Offset_DAC_Direct_Data(chan));
	} else
		ni_writew(data[0] ^ invert,
			  (chan) ? DAC1_Direct_Data : DAC0_Direct_Data);

	return 1;
}