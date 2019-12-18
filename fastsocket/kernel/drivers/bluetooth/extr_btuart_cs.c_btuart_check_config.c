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
struct TYPE_14__ {scalar_t__ BasePort1; int IOAddrLines; } ;
struct TYPE_9__ {int Vpp; } ;
struct pcmcia_device {TYPE_6__ io; TYPE_1__ conf; } ;
struct TYPE_12__ {scalar_t__ nwin; int flags; TYPE_3__* win; } ;
struct TYPE_10__ {int present; int* param; } ;
struct TYPE_13__ {TYPE_4__ io; TYPE_2__ vpp1; } ;
typedef  TYPE_5__ cistpl_cftable_entry_t ;
struct TYPE_11__ {int len; scalar_t__ base; } ;

/* Variables and functions */
 int CISTPL_IO_LINES_MASK ; 
 int CISTPL_POWER_VNOM ; 
 int ENODEV ; 
 int /*<<< orphan*/  pcmcia_request_io (struct pcmcia_device*,TYPE_6__*) ; 

__attribute__((used)) static int btuart_check_config(struct pcmcia_device *p_dev,
			       cistpl_cftable_entry_t *cf,
			       cistpl_cftable_entry_t *dflt,
			       unsigned int vcc,
			       void *priv_data)
{
	int *try = priv_data;

	if (cf->vpp1.present & (1 << CISTPL_POWER_VNOM))
		p_dev->conf.Vpp = cf->vpp1.param[CISTPL_POWER_VNOM] / 10000;
	if ((cf->io.nwin > 0) && (cf->io.win[0].len == 8) &&
	    (cf->io.win[0].base != 0)) {
		p_dev->io.BasePort1 = cf->io.win[0].base;
		p_dev->io.IOAddrLines = (*try == 0) ? 16 :
			cf->io.flags & CISTPL_IO_LINES_MASK;
		if (!pcmcia_request_io(p_dev, &p_dev->io))
			return 0;
	}
	return -ENODEV;
}