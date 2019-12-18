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
struct TYPE_2__ {unsigned int* s68k_regs; } ;

/* Variables and functions */
 TYPE_1__* Pico_mcd ; 
 scalar_t__ psp_screen ; 

__attribute__((used)) static void cd_leds(void)
{
	unsigned int reg, col_g, col_r, *p;

	reg = Pico_mcd->s68k_regs[0];

	p = (unsigned int *)((short *)psp_screen + 512*2+4+2);
	col_g = (reg & 2) ? 0x06000600 : 0;
	col_r = (reg & 1) ? 0x00180018 : 0;
	*p++ = col_g; *p++ = col_g; p+=2; *p++ = col_r; *p++ = col_r; p += 512/2 - 12/2;
	*p++ = col_g; *p++ = col_g; p+=2; *p++ = col_r; *p++ = col_r; p += 512/2 - 12/2;
	*p++ = col_g; *p++ = col_g; p+=2; *p++ = col_r; *p++ = col_r;
}