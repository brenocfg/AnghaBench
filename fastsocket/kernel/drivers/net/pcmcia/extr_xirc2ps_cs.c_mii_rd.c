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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  SelectPage (int) ; 
 scalar_t__ mii_getbit (unsigned int) ; 
 int /*<<< orphan*/  mii_idle (unsigned int) ; 
 int /*<<< orphan*/  mii_putbit (unsigned int,int) ; 
 int /*<<< orphan*/  mii_wbits (unsigned int,int,int) ; 

__attribute__((used)) static unsigned
mii_rd(unsigned int ioaddr,	u_char phyaddr, u_char phyreg)
{
    int i;
    unsigned data=0, m;

    SelectPage(2);
    for (i=0; i < 32; i++)		/* 32 bit preamble */
	mii_putbit(ioaddr, 1);
    mii_wbits(ioaddr, 0x06, 4); 	/* Start and opcode for read */
    mii_wbits(ioaddr, phyaddr, 5);	/* PHY address to be accessed */
    mii_wbits(ioaddr, phyreg, 5);	/* PHY register to read */
    mii_idle(ioaddr);			/* turn around */
    mii_getbit(ioaddr);

    for (m = 1<<15; m; m >>= 1)
	if (mii_getbit(ioaddr))
	    data |= m;
    mii_idle(ioaddr);
    return data;
}