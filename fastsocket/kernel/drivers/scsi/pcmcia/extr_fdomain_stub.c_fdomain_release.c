#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ scsi_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdomain_release(struct pcmcia_device *link)
{
	scsi_info_t *info = link->priv;

	DEBUG(0, "fdomain_release(0x%p)\n", link);

	scsi_remove_host(info->host);
	pcmcia_disable_device(link);
	scsi_unregister(info->host);
}