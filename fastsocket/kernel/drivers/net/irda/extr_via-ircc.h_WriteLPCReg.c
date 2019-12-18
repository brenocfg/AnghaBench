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
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void WriteLPCReg(int iRegNum, unsigned char iVal)
{

	outb(0x87, 0x2e);
	outb(0x87, 0x2e);
	outb(iRegNum, 0x2e);
	outb(iVal, 0x2f);
	outb(0xAA, 0x2e);
}