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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int SE2CLK ; 
 int SE2CS ; 
 int SE2DI ; 
 scalar_t__ TUL_NVRAM ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  initio_se2_instr (unsigned long,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u16 initio_se2_rd(unsigned long base, u8 addr)
{
	u8 instr, rb;
	u16 val = 0;
	int i;

	instr = (u8) (addr | 0x80);
	initio_se2_instr(base, instr);	/* READ INSTR */

	for (i = 15; i >= 0; i--) {
		outb(SE2CS | SE2CLK, base + TUL_NVRAM);	/* +CLK */
		udelay(30);
		outb(SE2CS, base + TUL_NVRAM);		/* -CLK */

		/* sample data after the following edge of clock  */
		rb = inb(base + TUL_NVRAM);
		rb &= SE2DI;
		val += (rb << i);
		udelay(30);	/* 6/20/95 */
	}

	outb(0, base + TUL_NVRAM);		/* no chip select */
	udelay(30);
	return val;
}