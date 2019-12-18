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
typedef  int /*<<< orphan*/  u_char ;
struct smc_private {scalar_t__ base; } ;
struct TYPE_2__ {scalar_t__ ConfigBase; } ;
struct pcmcia_device {TYPE_1__ conf; struct net_device* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CISREG_COR ; 
 scalar_t__ MEGAHERTZ_ISR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mhz_3288_power(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    struct smc_private *smc = netdev_priv(dev);
    u_char tmp;

    /* Read the ISR twice... */
    readb(smc->base+MEGAHERTZ_ISR);
    udelay(5);
    readb(smc->base+MEGAHERTZ_ISR);

    /* Pause 200ms... */
    mdelay(200);

    /* Now read and write the COR... */
    tmp = readb(smc->base + link->conf.ConfigBase + CISREG_COR);
    udelay(5);
    writeb(tmp, smc->base + link->conf.ConfigBase + CISREG_COR);

    return 0;
}