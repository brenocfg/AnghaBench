#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* s68k_regs; } ;

/* Variables and functions */
 TYPE_1__* Pico_mcd ; 
 scalar_t__ giz_screen ; 

__attribute__((used)) static void cd_leds(void)
{
	static int old_reg = 0;
	unsigned int col_g, col_r, *p;

	if (!((Pico_mcd->s68k_regs[0] ^ old_reg) & 3)) return; // no change
	old_reg = Pico_mcd->s68k_regs[0];

	p = (unsigned int *)((short *)giz_screen + 321*2+4+2);
	col_g = (old_reg & 2) ? 0x06000600 : 0;
	col_r = (old_reg & 1) ? 0xc000c000 : 0;
	*p++ = col_g; *p++ = col_g; p+=2; *p++ = col_r; *p++ = col_r; p += 321/2 - 12/2 + 1;
	*p++ = col_g; p+=3; *p++ = col_r; p += 321/2 - 10/2;
	*p++ = col_g; *p++ = col_g; p+=2; *p++ = col_r; *p++ = col_r;
}