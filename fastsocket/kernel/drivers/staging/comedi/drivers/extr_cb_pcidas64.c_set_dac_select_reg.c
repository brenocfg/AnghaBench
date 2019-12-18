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
typedef  unsigned int uint16_t ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {scalar_t__ main_iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC_SELECT_REG ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static void set_dac_select_reg(struct comedi_device *dev,
			       const struct comedi_cmd *cmd)
{
	uint16_t bits;
	unsigned int first_channel, last_channel;

	first_channel = CR_CHAN(cmd->chanlist[0]);
	last_channel = CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]);
	if (last_channel < first_channel)
		comedi_error(dev, "bug! last ao channel < first ao channel");

	bits = (first_channel & 0x7) | (last_channel & 0x7) << 3;

	writew(bits, priv(dev)->main_iobase + DAC_SELECT_REG);
}