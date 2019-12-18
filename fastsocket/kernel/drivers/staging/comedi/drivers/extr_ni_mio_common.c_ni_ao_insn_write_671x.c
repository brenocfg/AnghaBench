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
struct TYPE_4__ {int aobits; } ;
struct TYPE_3__ {unsigned int* ao; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_Immediate_671x ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DACx_Direct_Data_671x (unsigned int) ; 
 int /*<<< orphan*/  ao_win_out (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  ni_ao_config_chanlist (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ao_insn_write_671x(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int invert;

	ao_win_out(1 << chan, AO_Immediate_671x);
	invert = 1 << (boardtype.aobits - 1);

	ni_ao_config_chanlist(dev, s, &insn->chanspec, 1, 0);

	devpriv->ao[chan] = data[0];
	ao_win_out(data[0] ^ invert, DACx_Direct_Data_671x(chan));

	return 1;
}