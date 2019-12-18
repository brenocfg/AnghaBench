#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int IOAddrLines; scalar_t__ NumPorts2; int /*<<< orphan*/  BasePort2; int /*<<< orphan*/  Attributes1; int /*<<< orphan*/  Attributes2; scalar_t__ NumPorts1; int /*<<< orphan*/  BasePort1; } ;
struct TYPE_25__ {int Vpp; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  Status; } ;
struct pcmcia_device {int /*<<< orphan*/  win; TYPE_13__ io; TYPE_5__ conf; } ;
struct TYPE_19__ {int Attributes; int Size; int /*<<< orphan*/  Base; scalar_t__ AccessSpeed; } ;
struct nsp_cs_configdata {TYPE_12__ req; TYPE_1__* data; } ;
struct TYPE_28__ {int /*<<< orphan*/  CardOffset; scalar_t__ Page; } ;
typedef  TYPE_8__ memreq_t ;
struct TYPE_29__ {scalar_t__ nwin; TYPE_7__* win; } ;
typedef  TYPE_9__ cistpl_mem_t ;
struct TYPE_17__ {scalar_t__ nwin; int flags; TYPE_6__* win; } ;
typedef  TYPE_10__ cistpl_io_t ;
struct TYPE_24__ {scalar_t__ IRQInfo1; } ;
struct TYPE_23__ {int present; int* param; } ;
struct TYPE_22__ {int present; int* param; } ;
struct TYPE_18__ {scalar_t__ index; int flags; TYPE_9__ mem; TYPE_10__ io; TYPE_4__ irq; TYPE_3__ vpp1; TYPE_2__ vcc; } ;
typedef  TYPE_11__ cistpl_cftable_entry_t ;
struct TYPE_27__ {int len; int /*<<< orphan*/  card_addr; int /*<<< orphan*/  host_addr; } ;
struct TYPE_26__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
struct TYPE_21__ {unsigned long MmioAddress; int MmioLength; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCSR_AUDIO_ENA ; 
 int CISTPL_CFTABLE_AUDIO ; 
 int CISTPL_IO_16BIT ; 
 int CISTPL_IO_8BIT ; 
 int CISTPL_IO_LINES_MASK ; 
 int CISTPL_POWER_VNOM ; 
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  CONF_ENABLE_SPKR ; 
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int /*<<< orphan*/  NSP_DEBUG_INIT ; 
 int WIN_DATA_WIDTH_16 ; 
 int WIN_ENABLE ; 
 int WIN_MEMORY_TYPE_CM ; 
 scalar_t__ ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_map_mem_page (int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ pcmcia_request_io (struct pcmcia_device*,TYPE_13__*) ; 
 scalar_t__ pcmcia_request_window (struct pcmcia_device**,TYPE_12__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nsp_cs_config_check(struct pcmcia_device *p_dev,
			       cistpl_cftable_entry_t *cfg,
			       cistpl_cftable_entry_t *dflt,
			       unsigned int vcc,
			       void *priv_data)
{
	struct nsp_cs_configdata *cfg_mem = priv_data;

	if (cfg->index == 0)
		return -ENODEV;

	/* Does this card need audio output? */
	if (cfg->flags & CISTPL_CFTABLE_AUDIO) {
		p_dev->conf.Attributes |= CONF_ENABLE_SPKR;
		p_dev->conf.Status = CCSR_AUDIO_ENA;
	}

	/* Use power settings for Vcc and Vpp if present */
	/*  Note that the CIS values need to be rescaled */
	if (cfg->vcc.present & (1<<CISTPL_POWER_VNOM)) {
		if (vcc != cfg->vcc.param[CISTPL_POWER_VNOM]/10000)
			return -ENODEV;
		else if (dflt->vcc.present & (1<<CISTPL_POWER_VNOM)) {
			if (vcc != dflt->vcc.param[CISTPL_POWER_VNOM]/10000)
				return -ENODEV;
		}

		if (cfg->vpp1.present & (1 << CISTPL_POWER_VNOM)) {
			p_dev->conf.Vpp =
				cfg->vpp1.param[CISTPL_POWER_VNOM] / 10000;
		} else if (dflt->vpp1.present & (1 << CISTPL_POWER_VNOM)) {
			p_dev->conf.Vpp =
				dflt->vpp1.param[CISTPL_POWER_VNOM] / 10000;
		}

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
			p_dev->io.IOAddrLines = io->flags & CISTPL_IO_LINES_MASK;
			p_dev->io.BasePort1 = io->win[0].base;
			p_dev->io.NumPorts1 = io->win[0].len;
			if (io->nwin > 1) {
				p_dev->io.Attributes2 = p_dev->io.Attributes1;
				p_dev->io.BasePort2 = io->win[1].base;
				p_dev->io.NumPorts2 = io->win[1].len;
			}
			/* This reserves IO space but doesn't actually enable it */
			if (pcmcia_request_io(p_dev, &p_dev->io) != 0)
				goto next_entry;
		}

		if ((cfg->mem.nwin > 0) || (dflt->mem.nwin > 0)) {
			memreq_t	map;
			cistpl_mem_t	*mem =
				(cfg->mem.nwin) ? &cfg->mem : &dflt->mem;
			cfg_mem->req.Attributes = WIN_DATA_WIDTH_16|WIN_MEMORY_TYPE_CM;
			cfg_mem->req.Attributes |= WIN_ENABLE;
			cfg_mem->req.Base = mem->win[0].host_addr;
			cfg_mem->req.Size = mem->win[0].len;
			if (cfg_mem->req.Size < 0x1000)
				cfg_mem->req.Size = 0x1000;
			cfg_mem->req.AccessSpeed = 0;
			if (pcmcia_request_window(&p_dev, &cfg_mem->req, &p_dev->win) != 0)
				goto next_entry;
			map.Page = 0; map.CardOffset = mem->win[0].card_addr;
			if (pcmcia_map_mem_page(p_dev->win, &map) != 0)
				goto next_entry;

			cfg_mem->data->MmioAddress = (unsigned long) ioremap_nocache(cfg_mem->req.Base, cfg_mem->req.Size);
			cfg_mem->data->MmioLength  = cfg_mem->req.Size;
		}
		/* If we got this far, we're cool! */
		return 0;
	}

next_entry:
	nsp_dbg(NSP_DEBUG_INIT, "next");
	pcmcia_disable_device(p_dev);
	return -ENODEV;
}