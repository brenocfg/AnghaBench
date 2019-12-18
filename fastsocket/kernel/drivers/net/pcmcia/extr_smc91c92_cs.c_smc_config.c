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
struct TYPE_2__ {int NumPorts1; int /*<<< orphan*/  BasePort1; } ;
struct pcmcia_device {TYPE_1__ io; struct net_device* priv; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_configcheck ; 

__attribute__((used)) static int smc_config(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    int i;

    link->io.NumPorts1 = 16;
    i = pcmcia_loop_config(link, smc_configcheck, NULL);
    if (!i)
	    dev->base_addr = link->io.BasePort1;

    return i;
}