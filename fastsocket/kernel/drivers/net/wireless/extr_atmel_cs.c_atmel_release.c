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
struct pcmcia_device {scalar_t__ priv; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* eth_dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  stop_atmel_card (struct net_device*) ; 

__attribute__((used)) static void atmel_release(struct pcmcia_device *link)
{
	struct net_device *dev = ((local_info_t*)link->priv)->eth_dev;

	DEBUG(0, "atmel_release(0x%p)\n", link);

	if (dev)
		stop_atmel_card(dev);
	((local_info_t*)link->priv)->eth_dev = NULL;

	pcmcia_disable_device(link);
}