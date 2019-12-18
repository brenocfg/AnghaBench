#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ NumPorts2; int /*<<< orphan*/  BasePort2; int /*<<< orphan*/  Attributes1; int /*<<< orphan*/  Attributes2; scalar_t__ NumPorts1; int /*<<< orphan*/  BasePort1; } ;
struct TYPE_12__ {int Vpp; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  Status; } ;
struct pcmcia_device {TYPE_7__ io; TYPE_3__ conf; } ;
struct TYPE_14__ {scalar_t__ nwin; int flags; TYPE_4__* win; } ;
typedef  TYPE_5__ cistpl_io_t ;
struct TYPE_11__ {scalar_t__ IRQInfo1; } ;
struct TYPE_10__ {int present; int* param; } ;
struct TYPE_15__ {scalar_t__ index; int flags; TYPE_5__ io; TYPE_2__ irq; TYPE_1__ vpp1; } ;
typedef  TYPE_6__ cistpl_cftable_entry_t ;
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCSR_AUDIO_ENA ; 
 int CISTPL_CFTABLE_AUDIO ; 
 int CISTPL_IO_16BIT ; 
 int CISTPL_IO_8BIT ; 
 int CISTPL_POWER_VNOM ; 
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  CONF_ENABLE_SPKR ; 
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int pcmcia_request_io (struct pcmcia_device*,TYPE_7__*) ; 

__attribute__((used)) static int atmel_config_check(struct pcmcia_device *p_dev,
			      cistpl_cftable_entry_t *cfg,
			      cistpl_cftable_entry_t *dflt,
			      unsigned int vcc,
			      void *priv_data)
{
	if (cfg->index == 0)
		return -ENODEV;

	/* Does this card need audio output? */
	if (cfg->flags & CISTPL_CFTABLE_AUDIO) {
		p_dev->conf.Attributes |= CONF_ENABLE_SPKR;
		p_dev->conf.Status = CCSR_AUDIO_ENA;
	}

	/* Use power settings for Vcc and Vpp if present */
	/*  Note that the CIS values need to be rescaled */
	if (cfg->vpp1.present & (1<<CISTPL_POWER_VNOM))
		p_dev->conf.Vpp = cfg->vpp1.param[CISTPL_POWER_VNOM]/10000;
	else if (dflt->vpp1.present & (1<<CISTPL_POWER_VNOM))
		p_dev->conf.Vpp = dflt->vpp1.param[CISTPL_POWER_VNOM]/10000;

	/* Do we need to allocate an interrupt? */
	if (cfg->irq.IRQInfo1 || dflt->irq.IRQInfo1)
		p_dev->conf.Attributes |= CONF_ENABLE_IRQ;

	/* IO window settings */
	p_dev->io.NumPorts1 = p_dev->io.NumPorts2 = 0;
	if ((cfg->io.nwin > 0) || (dflt->io.nwin > 0)) {
		cistpl_io_t *io = (cfg->io.nwin) ? &cfg->io : &dflt->io;
		p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_AUTO;
		if (!(io->flags & CISTPL_IO_8BIT))
			p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_16;
		if (!(io->flags & CISTPL_IO_16BIT))
			p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
		p_dev->io.BasePort1 = io->win[0].base;
		p_dev->io.NumPorts1 = io->win[0].len;
		if (io->nwin > 1) {
			p_dev->io.Attributes2 = p_dev->io.Attributes1;
			p_dev->io.BasePort2 = io->win[1].base;
			p_dev->io.NumPorts2 = io->win[1].len;
		}
	}

	/* This reserves IO space but doesn't actually enable it */
	return pcmcia_request_io(p_dev, &p_dev->io);
}