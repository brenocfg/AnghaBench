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
 int /*<<< orphan*/  VGA_GFX_BIT_MASK ; 
 int /*<<< orphan*/  VGA_GFX_COMPARE_MASK ; 
 int /*<<< orphan*/  VGA_GFX_COMPARE_VALUE ; 
 int /*<<< orphan*/  VGA_GFX_DATA_ROTATE ; 
 int /*<<< orphan*/  VGA_GFX_MISC ; 
 int /*<<< orphan*/  VGA_GFX_MODE ; 
 int /*<<< orphan*/  VGA_GFX_PLANE_READ ; 
 int /*<<< orphan*/  VGA_GFX_SR_ENABLE ; 
 int /*<<< orphan*/  VGA_GFX_SR_VALUE ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void svga_set_default_gfx_regs(void)
{
	/* All standard GFX registers (GR00 - GR08) */
	vga_wgfx(NULL, VGA_GFX_SR_VALUE, 0x00);
	vga_wgfx(NULL, VGA_GFX_SR_ENABLE, 0x00);
	vga_wgfx(NULL, VGA_GFX_COMPARE_VALUE, 0x00);
	vga_wgfx(NULL, VGA_GFX_DATA_ROTATE, 0x00);
	vga_wgfx(NULL, VGA_GFX_PLANE_READ, 0x00);
	vga_wgfx(NULL, VGA_GFX_MODE, 0x00);
/*	vga_wgfx(NULL, VGA_GFX_MODE, 0x20); */
/*	vga_wgfx(NULL, VGA_GFX_MODE, 0x40); */
	vga_wgfx(NULL, VGA_GFX_MISC, 0x05);
/*	vga_wgfx(NULL, VGA_GFX_MISC, 0x01); */
	vga_wgfx(NULL, VGA_GFX_COMPARE_MASK, 0x0F);
	vga_wgfx(NULL, VGA_GFX_BIT_MASK, 0xFF);
}