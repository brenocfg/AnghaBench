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
typedef  int /*<<< orphan*/  u8 ;
struct savagefb_par {scalar_t__ paletteEnabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  vga_in8 (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out8 (int,int,struct savagefb_par*) ; 

__attribute__((used)) static inline void VGAdisablePalette(struct savagefb_par *par)
{
	u8 tmp;

	tmp = vga_in8(0x3da, par);
	vga_out8(0x3c0, 0x20, par);
	par->paletteEnabled = 0;
}