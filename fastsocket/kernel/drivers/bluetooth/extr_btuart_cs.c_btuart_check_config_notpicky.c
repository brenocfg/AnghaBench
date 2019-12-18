#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int BasePort1; int IOAddrLines; } ;
struct pcmcia_device {TYPE_3__ io; } ;
struct TYPE_6__ {scalar_t__ nwin; int flags; } ;
struct TYPE_7__ {TYPE_1__ io; } ;
typedef  TYPE_2__ cistpl_cftable_entry_t ;

/* Variables and functions */
 int CISTPL_IO_LINES_MASK ; 
 int ENODEV ; 
 int /*<<< orphan*/  pcmcia_request_io (struct pcmcia_device*,TYPE_3__*) ; 

__attribute__((used)) static int btuart_check_config_notpicky(struct pcmcia_device *p_dev,
					cistpl_cftable_entry_t *cf,
					cistpl_cftable_entry_t *dflt,
					unsigned int vcc,
					void *priv_data)
{
	static unsigned int base[5] = { 0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x0 };
	int j;

	if ((cf->io.nwin > 0) && ((cf->io.flags & CISTPL_IO_LINES_MASK) <= 3)) {
		for (j = 0; j < 5; j++) {
			p_dev->io.BasePort1 = base[j];
			p_dev->io.IOAddrLines = base[j] ? 16 : 3;
			if (!pcmcia_request_io(p_dev, &p_dev->io))
				return 0;
		}
	}
	return -ENODEV;
}