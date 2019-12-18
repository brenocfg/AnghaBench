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
struct TYPE_10__ {int NumPorts1; int IOAddrLines; int /*<<< orphan*/  BasePort1; } ;
struct pcmcia_device {TYPE_4__ io; } ;
struct TYPE_8__ {int nwin; int flags; TYPE_1__* win; } ;
struct TYPE_9__ {TYPE_2__ io; } ;
typedef  TYPE_3__ cistpl_cftable_entry_t ;
struct TYPE_7__ {int len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int CISTPL_IO_LINES_MASK ; 
 int ENODEV ; 
 int /*<<< orphan*/  pcmcia_request_io (struct pcmcia_device*,TYPE_4__*) ; 

__attribute__((used)) static int dtl1_confcheck(struct pcmcia_device *p_dev,
			  cistpl_cftable_entry_t *cf,
			  cistpl_cftable_entry_t *dflt,
			  unsigned int vcc,
			  void *priv_data)
{
	if ((cf->io.nwin == 1) && (cf->io.win[0].len > 8)) {
		p_dev->io.BasePort1 = cf->io.win[0].base;
		p_dev->io.NumPorts1 = cf->io.win[0].len;	/*yo */
		p_dev->io.IOAddrLines = cf->io.flags & CISTPL_IO_LINES_MASK;
		if (!pcmcia_request_io(p_dev, &p_dev->io))
			return 0;
	}
	return -ENODEV;
}