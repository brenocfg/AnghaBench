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

/* Variables and functions */
 int MDIO_DATA_READ ; 
 int MDIO_DATA_WRITE0 ; 
 int MDIO_DATA_WRITE1 ; 
 int MDIO_ENB_IN ; 
 int MDIO_SHIFT_CLK ; 
 int inb_p (unsigned int) ; 
 int /*<<< orphan*/  mdio_sync (unsigned int) ; 
 int /*<<< orphan*/  outb_p (int,unsigned int) ; 

__attribute__((used)) static int mdio_read(unsigned int addr, int phy_id, int loc)
{
    u_int cmd = (0xf6<<10)|(phy_id<<5)|loc;
    int i, retval = 0;

    mdio_sync(addr);
    for (i = 14; i >= 0; i--) {
	int dat = (cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
	outb_p(dat, addr);
	outb_p(dat | MDIO_SHIFT_CLK, addr);
    }
    for (i = 19; i > 0; i--) {
	outb_p(MDIO_ENB_IN, addr);
	retval = (retval << 1) | ((inb_p(addr) & MDIO_DATA_READ) != 0);
	outb_p(MDIO_ENB_IN | MDIO_SHIFT_CLK, addr);
    }
    return (retval>>1) & 0xffff;
}