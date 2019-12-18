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
struct nvidia_par {int /*<<< orphan*/  PCIO; scalar_t__ paletteEnabled; scalar_t__ IOBase; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_ATT_IW ; 
 scalar_t__ VGA_ATT_R ; 
 int VGA_RD08 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

u8 NVReadAttr(struct nvidia_par *par, u8 index)
{
	volatile u8 tmp;

	tmp = VGA_RD08(par->PCIO, par->IOBase + 0x0a);
	if (par->paletteEnabled)
		index &= ~0x20;
	else
		index |= 0x20;
	VGA_WR08(par->PCIO, VGA_ATT_IW, index);
	return (VGA_RD08(par->PCIO, VGA_ATT_R));
}