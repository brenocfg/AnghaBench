#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int IOAddrLines; int /*<<< orphan*/  NumPorts2; int /*<<< orphan*/  BasePort2; int /*<<< orphan*/  NumPorts1; int /*<<< orphan*/  BasePort1; } ;
struct TYPE_8__ {int /*<<< orphan*/  ConfigIndex; } ;
struct pcmcia_device {TYPE_5__ io; TYPE_1__ conf; } ;
struct TYPE_10__ {scalar_t__ nwin; int flags; TYPE_2__* win; } ;
typedef  TYPE_3__ cistpl_io_t ;
struct TYPE_11__ {TYPE_3__ io; } ;
typedef  TYPE_4__ cistpl_cftable_entry_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int CISTPL_IO_LINES_MASK ; 
 int ENODEV ; 
 int /*<<< orphan*/  FORCE_EPP_MODE ; 
 scalar_t__ epp_mode ; 
 scalar_t__ pcmcia_request_io (struct pcmcia_device*,TYPE_5__*) ; 

__attribute__((used)) static int parport_config_check(struct pcmcia_device *p_dev,
				cistpl_cftable_entry_t *cfg,
				cistpl_cftable_entry_t *dflt,
				unsigned int vcc,
				void *priv_data)
{
	if ((cfg->io.nwin > 0) || (dflt->io.nwin > 0)) {
		cistpl_io_t *io = (cfg->io.nwin) ? &cfg->io : &dflt->io;
		if (epp_mode)
			p_dev->conf.ConfigIndex |= FORCE_EPP_MODE;
		p_dev->io.BasePort1 = io->win[0].base;
		p_dev->io.NumPorts1 = io->win[0].len;
		p_dev->io.IOAddrLines = io->flags & CISTPL_IO_LINES_MASK;
		if (io->nwin == 2) {
			p_dev->io.BasePort2 = io->win[1].base;
			p_dev->io.NumPorts2 = io->win[1].len;
		}
		if (pcmcia_request_io(p_dev, &p_dev->io) != 0)
			return -ENODEV;
		return 0;
	}
	return -ENODEV;
}