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
 int VGA_CRTC_MAX_SCAN ; 
 int /*<<< orphan*/  VGA_CRTC_MODE ; 
 int /*<<< orphan*/  VGA_CRTC_PRESET_ROW ; 
 int /*<<< orphan*/  VGA_CRTC_UNDERLINE ; 
 int /*<<< orphan*/  svga_wcrt_mask (int,int,int) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void svga_set_default_crt_regs(void)
{
	/* Standard CRT registers CR03 CR08 CR09 CR14 CR17 */
	svga_wcrt_mask(0x03, 0x80, 0x80);	/* Enable vertical retrace EVRA */
	vga_wcrt(NULL, VGA_CRTC_PRESET_ROW, 0);
	svga_wcrt_mask(VGA_CRTC_MAX_SCAN, 0, 0x1F);
	vga_wcrt(NULL, VGA_CRTC_UNDERLINE, 0);
	vga_wcrt(NULL, VGA_CRTC_MODE, 0xE3);
}