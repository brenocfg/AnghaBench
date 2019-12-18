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
struct net_device {unsigned int base_addr; int flags; int mc_count; } ;

/* Variables and functions */
 unsigned int EnableRecv ; 
 int GetByte (int /*<<< orphan*/ ) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 unsigned int Offline ; 
 unsigned int Online ; 
 int /*<<< orphan*/  PutByte (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SelectPage (int) ; 
 int /*<<< orphan*/  XIRCREG40_CMD0 ; 
 int /*<<< orphan*/  XIRCREG42_SWC1 ; 
 int /*<<< orphan*/  set_addresses (struct net_device*) ; 

__attribute__((used)) static void
set_multicast_list(struct net_device *dev)
{
    unsigned int ioaddr = dev->base_addr;
    unsigned value;

    SelectPage(0x42);
    value = GetByte(XIRCREG42_SWC1) & 0xC0;

    if (dev->flags & IFF_PROMISC) { /* snoop */
	PutByte(XIRCREG42_SWC1, value | 0x06); /* set MPE and PME */
    } else if (dev->mc_count > 9 || (dev->flags & IFF_ALLMULTI)) {
	PutByte(XIRCREG42_SWC1, value | 0x02); /* set MPE */
    } else if (dev->mc_count) {
	/* the chip can filter 9 addresses perfectly */
	PutByte(XIRCREG42_SWC1, value | 0x01);
	SelectPage(0x40);
	PutByte(XIRCREG40_CMD0, Offline);
	set_addresses(dev);
	SelectPage(0x40);
	PutByte(XIRCREG40_CMD0, EnableRecv | Online);
    } else { /* standard usage */
	PutByte(XIRCREG42_SWC1, value | 0x00);
    }
    SelectPage(0);
}