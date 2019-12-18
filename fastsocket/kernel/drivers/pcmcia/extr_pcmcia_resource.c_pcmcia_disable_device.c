#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcmcia_device {scalar_t__ win; int /*<<< orphan*/  irq; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcmcia_release_configuration (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_release_io (struct pcmcia_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_release_irq (struct pcmcia_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_release_window (scalar_t__) ; 

void pcmcia_disable_device(struct pcmcia_device *p_dev) {
	pcmcia_release_configuration(p_dev);
	pcmcia_release_io(p_dev, &p_dev->io);
	pcmcia_release_irq(p_dev, &p_dev->irq);
	if (p_dev->win)
		pcmcia_release_window(p_dev->win);
}