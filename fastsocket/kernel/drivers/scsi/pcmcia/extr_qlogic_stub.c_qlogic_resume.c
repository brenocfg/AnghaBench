#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ BasePort1; } ;
struct pcmcia_device {TYPE_1__ io; int /*<<< orphan*/  conf; TYPE_2__* priv; } ;
struct TYPE_4__ {int manf_id; } ;
typedef  TYPE_2__ scsi_info_t ;

/* Variables and functions */
 int MANFID_MACNICA ; 
 int MANFID_PIONEER ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_request_configuration (struct pcmcia_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlogicfas408_bus_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlogic_resume(struct pcmcia_device *link)
{
	scsi_info_t *info = link->priv;

	pcmcia_request_configuration(link, &link->conf);
	if ((info->manf_id == MANFID_MACNICA) ||
	    (info->manf_id == MANFID_PIONEER) ||
	    (info->manf_id == 0x0098)) {
		outb(0x80, link->io.BasePort1 + 0xd);
		outb(0x24, link->io.BasePort1 + 0x9);
		outb(0x04, link->io.BasePort1 + 0xd);
	}
	/* Ugggglllyyyy!!! */
	qlogicfas408_bus_reset(NULL);

	return 0;
}