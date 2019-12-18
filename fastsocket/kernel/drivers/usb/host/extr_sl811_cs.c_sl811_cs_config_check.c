#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {int IOAddrLines; scalar_t__ NumPorts1; int /*<<< orphan*/  BasePort1; int /*<<< orphan*/  Attributes1; scalar_t__ NumPorts2; } ;
struct TYPE_15__ {int Vpp; int /*<<< orphan*/  Attributes; } ;
struct pcmcia_device {TYPE_10__ io; TYPE_4__ conf; } ;
struct TYPE_17__ {scalar_t__ nwin; int flags; TYPE_5__* win; } ;
typedef  TYPE_6__ cistpl_io_t ;
struct TYPE_14__ {scalar_t__ IRQInfo1; } ;
struct TYPE_13__ {int present; int* param; } ;
struct TYPE_12__ {int present; int* param; } ;
struct TYPE_18__ {scalar_t__ index; TYPE_6__ io; TYPE_3__ irq; TYPE_2__ vpp1; TYPE_1__ vcc; } ;
typedef  TYPE_7__ cistpl_cftable_entry_t ;
struct TYPE_16__ {scalar_t__ len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int CISTPL_IO_LINES_MASK ; 
 int CISTPL_POWER_VNOM ; 
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int pcmcia_request_io (struct pcmcia_device*,TYPE_10__*) ; 

__attribute__((used)) static int sl811_cs_config_check(struct pcmcia_device *p_dev,
				 cistpl_cftable_entry_t *cfg,
				 cistpl_cftable_entry_t *dflt,
				 unsigned int vcc,
				 void *priv_data)
{
	if (cfg->index == 0)
		return -ENODEV;

	/* Use power settings for Vcc and Vpp if present */
	/*  Note that the CIS values need to be rescaled */
	if (cfg->vcc.present & (1<<CISTPL_POWER_VNOM)) {
		if (cfg->vcc.param[CISTPL_POWER_VNOM]/10000 != vcc)
			return -ENODEV;
	} else if (dflt->vcc.present & (1<<CISTPL_POWER_VNOM)) {
		if (dflt->vcc.param[CISTPL_POWER_VNOM]/10000 != vcc)
			return -ENODEV;
		}

	if (cfg->vpp1.present & (1<<CISTPL_POWER_VNOM))
		p_dev->conf.Vpp =
			cfg->vpp1.param[CISTPL_POWER_VNOM]/10000;
	else if (dflt->vpp1.present & (1<<CISTPL_POWER_VNOM))
		p_dev->conf.Vpp =
			dflt->vpp1.param[CISTPL_POWER_VNOM]/10000;

	/* we need an interrupt */
	if (cfg->irq.IRQInfo1 || dflt->irq.IRQInfo1)
		p_dev->conf.Attributes |= CONF_ENABLE_IRQ;

	/* IO window settings */
	p_dev->io.NumPorts1 = p_dev->io.NumPorts2 = 0;
	if ((cfg->io.nwin > 0) || (dflt->io.nwin > 0)) {
		cistpl_io_t *io = (cfg->io.nwin) ? &cfg->io : &dflt->io;

		p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
		p_dev->io.IOAddrLines = io->flags & CISTPL_IO_LINES_MASK;
		p_dev->io.BasePort1 = io->win[0].base;
		p_dev->io.NumPorts1 = io->win[0].len;

		return pcmcia_request_io(p_dev, &p_dev->io);
	}
	pcmcia_disable_device(p_dev);
	return -ENODEV;
}