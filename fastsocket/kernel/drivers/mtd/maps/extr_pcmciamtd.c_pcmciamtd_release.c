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
struct pcmciamtd_dev {int /*<<< orphan*/ * win_base; } ;
struct pcmcia_device {scalar_t__ win; struct pcmciamtd_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_release_window (scalar_t__) ; 

__attribute__((used)) static void pcmciamtd_release(struct pcmcia_device *link)
{
	struct pcmciamtd_dev *dev = link->priv;

	DEBUG(3, "link = 0x%p", link);

	if (link->win) {
		if(dev->win_base) {
			iounmap(dev->win_base);
			dev->win_base = NULL;
		}
		pcmcia_release_window(link->win);
	}
	pcmcia_disable_device(link);
}