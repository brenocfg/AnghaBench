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
 int /*<<< orphan*/  PutByte (scalar_t__,int) ; 
 int /*<<< orphan*/  PutWord (scalar_t__,int) ; 
 scalar_t__ XIRCREG2_GPR2 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mii_putbit(unsigned int ioaddr, unsigned data)
{
  #if 1
    if (data) {
	PutByte(XIRCREG2_GPR2, 0x0c|2|0); /* set MDIO */
	udelay(1);
	PutByte(XIRCREG2_GPR2, 0x0c|2|1); /* and drive MDCK high */
	udelay(1);
    } else {
	PutByte(XIRCREG2_GPR2, 0x0c|0|0); /* clear MDIO */
	udelay(1);
	PutByte(XIRCREG2_GPR2, 0x0c|0|1); /* and drive MDCK high */
	udelay(1);
    }
  #else
    if (data) {
	PutWord(XIRCREG2_GPR2-1, 0x0e0e);
	udelay(1);
	PutWord(XIRCREG2_GPR2-1, 0x0f0f);
	udelay(1);
    } else {
	PutWord(XIRCREG2_GPR2-1, 0x0c0c);
	udelay(1);
	PutWord(XIRCREG2_GPR2-1, 0x0d0d);
	udelay(1);
    }
  #endif
}