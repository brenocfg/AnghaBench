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

/* Variables and functions */
 unsigned int GetByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XIRCREG2_GPR2 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
mii_getbit(unsigned int ioaddr)
{
    unsigned d;

    PutByte(XIRCREG2_GPR2, 4|0); /* drive MDCK low */
    udelay(1);
    d = GetByte(XIRCREG2_GPR2); /* read MDIO */
    PutByte(XIRCREG2_GPR2, 4|1); /* drive MDCK high again */
    udelay(1);
    return d & 0x20; /* read MDIO */
}