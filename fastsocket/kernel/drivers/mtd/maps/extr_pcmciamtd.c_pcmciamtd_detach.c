#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmciamtd_dev {TYPE_1__* mtd_info; } ;
struct pcmcia_device {struct pcmciamtd_dev* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  del_mtd_device (TYPE_1__*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  pcmciamtd_release (struct pcmcia_device*) ; 

__attribute__((used)) static void pcmciamtd_detach(struct pcmcia_device *link)
{
	struct pcmciamtd_dev *dev = link->priv;

	DEBUG(3, "link=0x%p", link);

	if(dev->mtd_info) {
		del_mtd_device(dev->mtd_info);
		map_destroy(dev->mtd_info);
		info("mtd%d: Removed", dev->mtd_info->index);
	}

	pcmciamtd_release(link);
}