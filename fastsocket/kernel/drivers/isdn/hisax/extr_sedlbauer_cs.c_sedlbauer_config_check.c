#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int Attributes; scalar_t__ AccessSpeed; int /*<<< orphan*/  Size; int /*<<< orphan*/  Base; } ;
typedef  TYPE_7__ win_req_t ;
struct TYPE_19__ {scalar_t__ NumPorts2; int /*<<< orphan*/  BasePort2; int /*<<< orphan*/  Attributes1; int /*<<< orphan*/  Attributes2; scalar_t__ NumPorts1; int /*<<< orphan*/  BasePort1; } ;
struct TYPE_23__ {int Vpp; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  Status; } ;
struct pcmcia_device {int /*<<< orphan*/  win; TYPE_15__ io; TYPE_4__ conf; } ;
struct TYPE_27__ {int /*<<< orphan*/  CardOffset; scalar_t__ Page; } ;
typedef  TYPE_8__ memreq_t ;
struct TYPE_28__ {scalar_t__ nwin; TYPE_6__* win; } ;
typedef  TYPE_9__ cistpl_mem_t ;
struct TYPE_17__ {scalar_t__ nwin; int flags; TYPE_5__* win; } ;
typedef  TYPE_10__ cistpl_io_t ;
struct TYPE_22__ {scalar_t__ IRQInfo1; } ;
struct TYPE_21__ {int present; int* param; } ;
struct TYPE_20__ {int present; int* param; } ;
struct TYPE_18__ {scalar_t__ index; int flags; TYPE_9__ mem; TYPE_10__ io; TYPE_3__ irq; TYPE_2__ vpp1; TYPE_1__ vcc; } ;
typedef  TYPE_11__ cistpl_cftable_entry_t ;
struct TYPE_25__ {int /*<<< orphan*/  card_addr; int /*<<< orphan*/  len; int /*<<< orphan*/  host_addr; } ;
struct TYPE_24__ {scalar_t__ len; int /*<<< orphan*/  base; } ;

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
 int WIN_DATA_WIDTH_16 ; 
 int WIN_ENABLE ; 
 int WIN_MEMORY_TYPE_CM ; 
 scalar_t__ pcmcia_map_mem_page (int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ pcmcia_request_io (struct pcmcia_device*,TYPE_15__*) ; 
 scalar_t__ pcmcia_request_window (struct pcmcia_device**,TYPE_7__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sedlbauer_config_check(struct pcmcia_device *p_dev,
				  cistpl_cftable_entry_t *cfg,
				  cistpl_cftable_entry_t *dflt,
				  unsigned int vcc,
				  void *priv_data)
{
	win_req_t *req = priv_data;

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
	} else if (dflt->vcc.present & (1<<CISTPL_POWER_VNOM)) {
		if (vcc != dflt->vcc.param[CISTPL_POWER_VNOM]/10000)
			return -ENODEV;
	}

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
		/* This reserves IO space but doesn't actually enable it */
		if (pcmcia_request_io(p_dev, &p_dev->io) != 0)
			return -ENODEV;
	}

	/*
	  Now set up a common memory window, if needed.  There is room
	  in the struct pcmcia_device structure for one memory window handle,
	  but if the base addresses need to be saved, or if multiple
	  windows are needed, the info should go in the private data
	  structure for this device.

	  Note that the memory window base is a physical address, and
	  needs to be mapped to virtual space with ioremap() before it
	  is used.
	*/
	if ((cfg->mem.nwin > 0) || (dflt->mem.nwin > 0)) {
		cistpl_mem_t *mem = (cfg->mem.nwin) ? &cfg->mem : &dflt->mem;
		memreq_t map;
		req->Attributes = WIN_DATA_WIDTH_16|WIN_MEMORY_TYPE_CM;
		req->Attributes |= WIN_ENABLE;
		req->Base = mem->win[0].host_addr;
		req->Size = mem->win[0].len;
		req->AccessSpeed = 0;
		if (pcmcia_request_window(&p_dev, req, &p_dev->win) != 0)
			return -ENODEV;
		map.Page = 0;
		map.CardOffset = mem->win[0].card_addr;
		if (pcmcia_map_mem_page(p_dev->win, &map) != 0)
			return -ENODEV;
	}
	return 0;
}