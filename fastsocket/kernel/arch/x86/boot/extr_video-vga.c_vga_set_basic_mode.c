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
struct biosregs {int ax; int al; } ;

/* Variables and functions */
 int do_restore ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 
 int rdfs8 (int) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 vga_set_basic_mode(void)
{
	struct biosregs ireg, oreg;
	u8 rows;
	u8 mode;

	initregs(&ireg);

	ireg.ax = 0x0f00;
	intcall(0x10, &ireg, &oreg);
	mode = oreg.al;

	set_fs(0);
	rows = rdfs8(0x484);	/* rows minus one */

	if ((oreg.ax == 0x5003 || oreg.ax == 0x5007) &&
	    (rows == 0 || rows == 24))
		return mode;

	if (mode != 3 && mode != 7)
		mode = 3;

	/* Set the mode */
	ireg.ax = mode;		/* AH=0: set mode */
	intcall(0x10, &ireg, NULL);
	do_restore = 1;
	return mode;
}