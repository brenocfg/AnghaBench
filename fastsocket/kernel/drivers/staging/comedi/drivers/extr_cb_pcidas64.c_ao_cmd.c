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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int stop_arg; int chanlist_len; } ;
struct TYPE_4__ {int ao_count; int ao_dma_desc_bus_addr; scalar_t__ ao_dma_index; scalar_t__ main_iobase; } ;
struct TYPE_3__ {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ DAC_CONTROL0_REG ; 
 int EBUSY ; 
 int PLX_DESC_IN_PCI_BIT ; 
 int PLX_INTR_TERM_COUNT ; 
 int /*<<< orphan*/  ao_inttrig ; 
 scalar_t__ external_ai_queue_in_use (struct comedi_device*) ; 
 int /*<<< orphan*/  load_first_dma_descriptor (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  set_dac_control1_reg (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  set_dac_interval_regs (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  set_dac_select_reg (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  warn_external_queue (struct comedi_device*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int ao_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;

	if (external_ai_queue_in_use(dev)) {
		warn_external_queue(dev);
		return -EBUSY;
	}
	/* disable analog output system during setup */
	writew(0x0, priv(dev)->main_iobase + DAC_CONTROL0_REG);

	priv(dev)->ao_dma_index = 0;
	priv(dev)->ao_count = cmd->stop_arg * cmd->chanlist_len;

	set_dac_select_reg(dev, cmd);
	set_dac_interval_regs(dev, cmd);
	load_first_dma_descriptor(dev, 0, priv(dev)->ao_dma_desc_bus_addr |
				  PLX_DESC_IN_PCI_BIT | PLX_INTR_TERM_COUNT);

	set_dac_control1_reg(dev, cmd);
	s->async->inttrig = ao_inttrig;

	return 0;
}