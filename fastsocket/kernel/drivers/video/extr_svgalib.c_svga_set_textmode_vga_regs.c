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
 int /*<<< orphan*/  VGA_ATT_W ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_END ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_HI ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_LO ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_START ; 
 int /*<<< orphan*/  VGA_CRTC_MAX_SCAN ; 
 int /*<<< orphan*/  VGA_CRTC_MODE ; 
 int /*<<< orphan*/  VGA_CRTC_UNDERLINE ; 
 int /*<<< orphan*/  VGA_GFX_COMPARE_MASK ; 
 int /*<<< orphan*/  VGA_GFX_MISC ; 
 int /*<<< orphan*/  VGA_GFX_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_MEMORY_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_PLANE_WRITE ; 
 int VGA_SR04_EXT_MEM ; 
 int /*<<< orphan*/  svga_wattr (int,int) ; 
 int /*<<< orphan*/  svga_wcrt_mask (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vga_r (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void svga_set_textmode_vga_regs(void)
{
	/* svga_wseq_mask(0x1, 0x00, 0x01); */   /* Switch 8/9 pixel per char */
	vga_wseq(NULL, VGA_SEQ_MEMORY_MODE,	VGA_SR04_EXT_MEM);
	vga_wseq(NULL, VGA_SEQ_PLANE_WRITE,	0x03);

	vga_wcrt(NULL, VGA_CRTC_MAX_SCAN,	0x0f); /* 0x4f */
	vga_wcrt(NULL, VGA_CRTC_UNDERLINE,	0x1f);
	svga_wcrt_mask(VGA_CRTC_MODE,		0x23, 0x7f);

	vga_wcrt(NULL, VGA_CRTC_CURSOR_START,	0x0d);
	vga_wcrt(NULL, VGA_CRTC_CURSOR_END,	0x0e);
	vga_wcrt(NULL, VGA_CRTC_CURSOR_HI,	0x00);
	vga_wcrt(NULL, VGA_CRTC_CURSOR_LO,	0x00);

	vga_wgfx(NULL, VGA_GFX_MODE,		0x10); /* Odd/even memory mode */
	vga_wgfx(NULL, VGA_GFX_MISC,		0x0E); /* Misc graphics register - text mode enable */
	vga_wgfx(NULL, VGA_GFX_COMPARE_MASK,	0x00);

	vga_r(NULL, 0x3DA);
	vga_w(NULL, VGA_ATT_W, 0x00);

	svga_wattr(0x10, 0x0C);			/* Attribute Mode Control Register - text mode, blinking and line graphics */
	svga_wattr(0x13, 0x08);			/* Horizontal Pixel Panning Register  */

	vga_r(NULL, 0x3DA);
	vga_w(NULL, VGA_ATT_W, 0x20);
}