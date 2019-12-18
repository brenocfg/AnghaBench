#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int BasePort1; } ;
struct pcmcia_device {TYPE_4__ io; } ;
struct TYPE_8__ {int nwin; TYPE_1__* win; } ;
struct TYPE_9__ {TYPE_2__ io; } ;
typedef  TYPE_3__ cistpl_cftable_entry_t ;
struct TYPE_7__ {int len; int base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pcmcia_request_io (struct pcmcia_device*,TYPE_4__*) ; 

__attribute__((used)) static int aha152x_config_check(struct pcmcia_device *p_dev,
				cistpl_cftable_entry_t *cfg,
				cistpl_cftable_entry_t *dflt,
				unsigned int vcc,
				void *priv_data)
{
	/* For New Media T&J, look for a SCSI window */
	if (cfg->io.win[0].len >= 0x20)
		p_dev->io.BasePort1 = cfg->io.win[0].base;
	else if ((cfg->io.nwin > 1) &&
		 (cfg->io.win[1].len >= 0x20))
		p_dev->io.BasePort1 = cfg->io.win[1].base;
	if ((cfg->io.nwin > 0) &&
	    (p_dev->io.BasePort1 < 0xffff)) {
		if (!pcmcia_request_io(p_dev, &p_dev->io))
			return 0;
	}
	return -EINVAL;
}