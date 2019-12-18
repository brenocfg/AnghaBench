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
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {scalar_t__ main_iobase; int /*<<< orphan*/  dac_control1_bits; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC_CONTROL1_REG ; 
 int /*<<< orphan*/  DAC_SW_GATE_BIT ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  set_dac_range_bits (struct comedi_device*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void set_dac_control1_reg(struct comedi_device *dev,
				 const struct comedi_cmd *cmd)
{
	int i;

	for (i = 0; i < cmd->chanlist_len; i++) {
		int channel, range;

		channel = CR_CHAN(cmd->chanlist[i]);
		range = CR_RANGE(cmd->chanlist[i]);
		set_dac_range_bits(dev, &priv(dev)->dac_control1_bits, channel,
				   range);
	}
	priv(dev)->dac_control1_bits |= DAC_SW_GATE_BIT;
	writew(priv(dev)->dac_control1_bits,
	       priv(dev)->main_iobase + DAC_CONTROL1_REG);
}