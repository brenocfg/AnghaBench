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
struct ssb_bus {int dummy; } ;
struct pcmcia_device {struct ssb_bus* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ssb_bus*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  ssb_bus_unregister (struct ssb_bus*) ; 

__attribute__((used)) static void b43_pcmcia_remove(struct pcmcia_device *dev)
{
	struct ssb_bus *ssb = dev->priv;

	ssb_bus_unregister(ssb);
	pcmcia_disable_device(dev);
	kfree(ssb);
	dev->priv = NULL;
}