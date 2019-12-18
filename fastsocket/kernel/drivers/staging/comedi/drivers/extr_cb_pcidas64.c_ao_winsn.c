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
struct TYPE_4__ {scalar_t__ layout; } ;
struct TYPE_3__ {unsigned int dac_control1_bits; unsigned int* ao_value; scalar_t__ main_iobase; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC_CONTROL0_REG ; 
 scalar_t__ DAC_CONTROL1_REG ; 
 scalar_t__ LAYOUT_4020 ; 
 TYPE_2__* board (struct comedi_device*) ; 
 scalar_t__ dac_convert_reg (int) ; 
 scalar_t__ dac_lsb_4020_reg (int) ; 
 scalar_t__ dac_msb_4020_reg (int) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  set_dac_range_bits (struct comedi_device*,unsigned int*,int,int) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int ao_winsn(struct comedi_device *dev, struct comedi_subdevice *s,
		    struct comedi_insn *insn, unsigned int *data)
{
	int chan = CR_CHAN(insn->chanspec);
	int range = CR_RANGE(insn->chanspec);

	/*  do some initializing */
	writew(0, priv(dev)->main_iobase + DAC_CONTROL0_REG);

	/*  set range */
	set_dac_range_bits(dev, &priv(dev)->dac_control1_bits, chan, range);
	writew(priv(dev)->dac_control1_bits,
	       priv(dev)->main_iobase + DAC_CONTROL1_REG);

	/*  write to channel */
	if (board(dev)->layout == LAYOUT_4020) {
		writew(data[0] & 0xff,
		       priv(dev)->main_iobase + dac_lsb_4020_reg(chan));
		writew((data[0] >> 8) & 0xf,
		       priv(dev)->main_iobase + dac_msb_4020_reg(chan));
	} else {
		writew(data[0], priv(dev)->main_iobase + dac_convert_reg(chan));
	}

	/*  remember output value */
	priv(dev)->ao_value[chan] = data[0];

	return 1;
}