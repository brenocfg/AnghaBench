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
struct net_device {scalar_t__ base_addr; } ;
struct frad_local {int type; int state; } ;

/* Variables and functions */
 int SDLA_CPUEN ; 
 scalar_t__ SDLA_REG_CONTROL ; 
 scalar_t__ SDLA_REG_Z80_CONTROL ; 
#define  SDLA_S502A 131 
 int SDLA_S502A_NMI ; 
 int SDLA_S502A_START ; 
#define  SDLA_S502E 130 
 int SDLA_S502E_CPUEN ; 
#define  SDLA_S507 129 
#define  SDLA_S508 128 
 struct frad_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void sdla_start(struct net_device *dev)
{
	struct frad_local *flp;

	flp = netdev_priv(dev);
	switch(flp->type)
	{
		case SDLA_S502A:
			outb(SDLA_S502A_NMI, dev->base_addr + SDLA_REG_CONTROL);
			outb(SDLA_S502A_START, dev->base_addr + SDLA_REG_CONTROL);
			flp->state = SDLA_S502A_START;
			break;
		case SDLA_S502E:
			outb(SDLA_S502E_CPUEN, dev->base_addr + SDLA_REG_Z80_CONTROL);
			outb(0x00, dev->base_addr + SDLA_REG_CONTROL);
			flp->state = 0;
			break;
		case SDLA_S507:
			flp->state |= SDLA_CPUEN;
			outb(flp->state, dev->base_addr + SDLA_REG_CONTROL);
			break;
		case SDLA_S508:
			flp->state |= SDLA_CPUEN;
			outb(flp->state, dev->base_addr + SDLA_REG_CONTROL);
			break;
	}
}