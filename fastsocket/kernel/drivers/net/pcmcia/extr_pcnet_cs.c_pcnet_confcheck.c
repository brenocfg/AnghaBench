#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ NumPorts2; scalar_t__ NumPorts1; int IOAddrLines; int /*<<< orphan*/  BasePort1; int /*<<< orphan*/  BasePort2; } ;
struct pcmcia_device {TYPE_4__ io; } ;
struct TYPE_13__ {scalar_t__ nwin; int flags; TYPE_3__* win; } ;
typedef  TYPE_5__ cistpl_io_t ;
struct TYPE_10__ {int nwin; TYPE_1__* win; } ;
struct TYPE_14__ {scalar_t__ index; TYPE_2__ mem; TYPE_5__ io; } ;
typedef  TYPE_6__ cistpl_cftable_entry_t ;
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
struct TYPE_9__ {int len; } ;

/* Variables and functions */
 int CISTPL_IO_LINES_MASK ; 
 int EINVAL ; 
 int try_io_port (struct pcmcia_device*) ; 

__attribute__((used)) static int pcnet_confcheck(struct pcmcia_device *p_dev,
			   cistpl_cftable_entry_t *cfg,
			   cistpl_cftable_entry_t *dflt,
			   unsigned int vcc,
			   void *priv_data)
{
	int *has_shmem = priv_data;
	int i;
	cistpl_io_t *io = &cfg->io;

	if (cfg->index == 0 || cfg->io.nwin == 0)
		return -EINVAL;

	/* For multifunction cards, by convention, we configure the
	   network function with window 0, and serial with window 1 */
	if (io->nwin > 1) {
		i = (io->win[1].len > io->win[0].len);
		p_dev->io.BasePort2 = io->win[1-i].base;
		p_dev->io.NumPorts2 = io->win[1-i].len;
	} else {
		i = p_dev->io.NumPorts2 = 0;
	}

	*has_shmem = ((cfg->mem.nwin == 1) &&
		      (cfg->mem.win[0].len >= 0x4000));
	p_dev->io.BasePort1 = io->win[i].base;
	p_dev->io.NumPorts1 = io->win[i].len;
	p_dev->io.IOAddrLines = io->flags & CISTPL_IO_LINES_MASK;
	if (p_dev->io.NumPorts1 + p_dev->io.NumPorts2 >= 32)
		return try_io_port(p_dev);

	return 0;
}