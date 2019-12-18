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
struct smc_private {scalar_t__ base; } ;
struct TYPE_2__ {unsigned int BasePort2; } ;
struct pcmcia_device {TYPE_1__ io; struct net_device* priv; } ;
struct net_device {unsigned int base_addr; } ;

/* Variables and functions */
 scalar_t__ CISREG_COR ; 
 scalar_t__ CISREG_IOBASE_0 ; 
 scalar_t__ CISREG_IOBASE_1 ; 
 scalar_t__ MOT_LAN ; 
 unsigned int MOT_NORMAL ; 
 scalar_t__ MOT_UART ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mot_config(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    struct smc_private *smc = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;
    unsigned int iouart = link->io.BasePort2;

    /* Set UART base address and force map with COR bit 1 */
    writeb(iouart & 0xff,        smc->base + MOT_UART + CISREG_IOBASE_0);
    writeb((iouart >> 8) & 0xff, smc->base + MOT_UART + CISREG_IOBASE_1);
    writeb(MOT_NORMAL,           smc->base + MOT_UART + CISREG_COR);

    /* Set SMC base address and force map with COR bit 1 */
    writeb(ioaddr & 0xff,        smc->base + MOT_LAN + CISREG_IOBASE_0);
    writeb((ioaddr >> 8) & 0xff, smc->base + MOT_LAN + CISREG_IOBASE_1);
    writeb(MOT_NORMAL,           smc->base + MOT_LAN + CISREG_COR);

    /* Wait for things to settle down */
    mdelay(100);
}