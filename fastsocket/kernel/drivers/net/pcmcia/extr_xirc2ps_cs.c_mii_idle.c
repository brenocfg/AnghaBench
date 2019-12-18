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
 int /*<<< orphan*/  PutByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XIRCREG2_GPR2 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mii_idle(unsigned int ioaddr)
{
    PutByte(XIRCREG2_GPR2, 0x04|0); /* drive MDCK low */
    udelay(1);
    PutByte(XIRCREG2_GPR2, 0x04|1); /* and drive MDCK high */
    udelay(1);
}