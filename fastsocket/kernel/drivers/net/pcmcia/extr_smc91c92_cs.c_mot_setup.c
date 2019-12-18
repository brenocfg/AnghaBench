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
typedef  int u_int ;
struct pcmcia_device {struct net_device* priv; } ;
struct net_device {unsigned int base_addr; int* dev_addr; } ;

/* Variables and functions */
 scalar_t__ CONTROL ; 
 int CTL_EE_SELECT ; 
 int CTL_RELOAD ; 
 int CTL_STORE ; 
 scalar_t__ GENERAL ; 
 int MOT_EEPROM ; 
 scalar_t__ POINTER ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mot_setup(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    unsigned int ioaddr = dev->base_addr;
    int i, wait, loop;
    u_int addr;

    /* Read Ethernet address from Serial EEPROM */

    for (i = 0; i < 3; i++) {
	SMC_SELECT_BANK(2);
	outw(MOT_EEPROM + i, ioaddr + POINTER);
	SMC_SELECT_BANK(1);
	outw((CTL_RELOAD | CTL_EE_SELECT), ioaddr + CONTROL);

	for (loop = wait = 0; loop < 200; loop++) {
	    udelay(10);
	    wait = ((CTL_RELOAD | CTL_STORE) & inw(ioaddr + CONTROL));
	    if (wait == 0) break;
	}
	
	if (wait)
	    return -1;
	
	addr = inw(ioaddr + GENERAL);
	dev->dev_addr[2*i]   = addr & 0xff;
	dev->dev_addr[2*i+1] = (addr >> 8) & 0xff;
    }

    return 0;
}