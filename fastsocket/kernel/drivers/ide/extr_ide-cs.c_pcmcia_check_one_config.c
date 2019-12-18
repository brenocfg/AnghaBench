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
struct TYPE_16__ {int IOAddrLines; int NumPorts1; int NumPorts2; scalar_t__ BasePort1; scalar_t__ BasePort2; int /*<<< orphan*/  Attributes1; } ;
struct TYPE_12__ {int Vpp; int /*<<< orphan*/  ConfigIndex; } ;
struct pcmcia_device {TYPE_7__ io; TYPE_3__ conf; } ;
struct pcmcia_config_check {scalar_t__ ctl_base; scalar_t__ is_kme; int /*<<< orphan*/  skip_vcc; } ;
struct TYPE_14__ {scalar_t__ nwin; int flags; TYPE_4__* win; } ;
typedef  TYPE_5__ cistpl_io_t ;
struct TYPE_11__ {int present; int* param; } ;
struct TYPE_10__ {int present; int* param; } ;
struct TYPE_15__ {int /*<<< orphan*/  index; TYPE_5__ io; TYPE_2__ vpp1; TYPE_1__ vcc; } ;
typedef  TYPE_6__ cistpl_cftable_entry_t ;
struct TYPE_13__ {int len; scalar_t__ base; } ;

/* Variables and functions */
 int CISTPL_IO_16BIT ; 
 int CISTPL_IO_LINES_MASK ; 
 int CISTPL_POWER_VNOM ; 
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 scalar_t__ pcmcia_request_io (struct pcmcia_device*,TYPE_7__*) ; 

__attribute__((used)) static int pcmcia_check_one_config(struct pcmcia_device *pdev,
				   cistpl_cftable_entry_t *cfg,
				   cistpl_cftable_entry_t *dflt,
				   unsigned int vcc,
				   void *priv_data)
{
	struct pcmcia_config_check *stk = priv_data;

	/* Check for matching Vcc, unless we're desperate */
	if (!stk->skip_vcc) {
		if (cfg->vcc.present & (1 << CISTPL_POWER_VNOM)) {
			if (vcc != cfg->vcc.param[CISTPL_POWER_VNOM] / 10000)
				return -ENODEV;
		} else if (dflt->vcc.present & (1 << CISTPL_POWER_VNOM)) {
			if (vcc != dflt->vcc.param[CISTPL_POWER_VNOM] / 10000)
				return -ENODEV;
		}
	}

	if (cfg->vpp1.present & (1 << CISTPL_POWER_VNOM))
		pdev->conf.Vpp = cfg->vpp1.param[CISTPL_POWER_VNOM] / 10000;
	else if (dflt->vpp1.present & (1 << CISTPL_POWER_VNOM))
		pdev->conf.Vpp = dflt->vpp1.param[CISTPL_POWER_VNOM] / 10000;

	if ((cfg->io.nwin > 0) || (dflt->io.nwin > 0)) {
		cistpl_io_t *io = (cfg->io.nwin) ? &cfg->io : &dflt->io;
		pdev->conf.ConfigIndex = cfg->index;
		pdev->io.BasePort1 = io->win[0].base;
		pdev->io.IOAddrLines = io->flags & CISTPL_IO_LINES_MASK;
		if (!(io->flags & CISTPL_IO_16BIT))
			pdev->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
		if (io->nwin == 2) {
			pdev->io.NumPorts1 = 8;
			pdev->io.BasePort2 = io->win[1].base;
			pdev->io.NumPorts2 = (stk->is_kme) ? 2 : 1;
			if (pcmcia_request_io(pdev, &pdev->io) != 0)
				return -ENODEV;
			stk->ctl_base = pdev->io.BasePort2;
		} else if ((io->nwin == 1) && (io->win[0].len >= 16)) {
			pdev->io.NumPorts1 = io->win[0].len;
			pdev->io.NumPorts2 = 0;
			if (pcmcia_request_io(pdev, &pdev->io) != 0)
				return -ENODEV;
			stk->ctl_base = pdev->io.BasePort1 + 0x0e;
		} else
			return -ENODEV;
		/* If we've got this far, we're done */
		return 0;
	}
	return -ENODEV;
}