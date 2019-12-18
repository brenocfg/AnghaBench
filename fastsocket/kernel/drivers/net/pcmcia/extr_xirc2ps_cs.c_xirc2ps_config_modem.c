#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int BasePort2; unsigned int BasePort1; } ;
struct pcmcia_device {TYPE_6__ io; } ;
struct TYPE_8__ {scalar_t__ nwin; TYPE_1__* win; } ;
struct TYPE_9__ {TYPE_2__ io; } ;
typedef  TYPE_3__ cistpl_cftable_entry_t ;
struct TYPE_7__ {int base; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  pcmcia_request_io (struct pcmcia_device*,TYPE_6__*) ; 

__attribute__((used)) static int
xirc2ps_config_modem(struct pcmcia_device *p_dev,
		     cistpl_cftable_entry_t *cf,
		     cistpl_cftable_entry_t *dflt,
		     unsigned int vcc,
		     void *priv_data)
{
	unsigned int ioaddr;

	if (cf->io.nwin > 0  &&  (cf->io.win[0].base & 0xf) == 8) {
		for (ioaddr = 0x300; ioaddr < 0x400; ioaddr += 0x10) {
			p_dev->io.BasePort2 = cf->io.win[0].base;
			p_dev->io.BasePort1 = ioaddr;
			if (!pcmcia_request_io(p_dev, &p_dev->io))
				return 0;
		}
	}
	return -ENODEV;
}