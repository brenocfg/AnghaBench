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
struct TYPE_10__ {scalar_t__ BasePort1; int /*<<< orphan*/  NumPorts1; } ;
struct pcmcia_device {TYPE_6__ io; } ;
struct TYPE_7__ {TYPE_2__* win; } ;
struct TYPE_9__ {TYPE_1__ io; } ;
typedef  TYPE_3__ cistpl_cftable_entry_t ;
struct TYPE_8__ {scalar_t__ base; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ENODEV ; 
 int pcmcia_request_io (struct pcmcia_device*,TYPE_6__*) ; 

__attribute__((used)) static int qlogic_config_check(struct pcmcia_device *p_dev,
			       cistpl_cftable_entry_t *cfg,
			       cistpl_cftable_entry_t *dflt,
			       unsigned int vcc,
			       void *priv_data)
{
	p_dev->io.BasePort1 = cfg->io.win[0].base;
	p_dev->io.NumPorts1 = cfg->io.win[0].len;

	if (p_dev->io.BasePort1 == 0)
		return -ENODEV;

	return pcmcia_request_io(p_dev, &p_dev->io);
}