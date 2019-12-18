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
typedef  int u8 ;
struct TYPE_2__ {unsigned int height; } ;
struct vc_data {TYPE_1__ vc_font; } ;

/* Variables and functions */
 int VGA_CRTC_H_DISP ; 
 int VGA_CRTC_MAX_SCAN ; 
 int VGA_CRTC_MODE ; 
 int VGA_CRTC_OFFSET ; 
 int VGA_CRTC_OVERFLOW ; 
 int VGA_CRTC_V_DISP_END ; 
 int VGA_CRTC_V_SYNC_END ; 
 unsigned int VGA_FONTWIDTH ; 
 scalar_t__ VIDEO_TYPE_VGAC ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vga_lock ; 
 int /*<<< orphan*/  vga_video_port_reg ; 
 int /*<<< orphan*/  vga_video_port_val ; 
 scalar_t__ vga_video_type ; 
 unsigned int vgacon_xres ; 
 unsigned int vgacon_yres ; 

__attribute__((used)) static int vgacon_doresize(struct vc_data *c,
		unsigned int width, unsigned int height)
{
	unsigned long flags;
	unsigned int scanlines = height * c->vc_font.height;
	u8 scanlines_lo = 0, r7 = 0, vsync_end = 0, mode, max_scan;

	spin_lock_irqsave(&vga_lock, flags);

	vgacon_xres = width * VGA_FONTWIDTH;
	vgacon_yres = height * c->vc_font.height;
	if (vga_video_type >= VIDEO_TYPE_VGAC) {
		outb_p(VGA_CRTC_MAX_SCAN, vga_video_port_reg);
		max_scan = inb_p(vga_video_port_val);

		if (max_scan & 0x80)
			scanlines <<= 1;

		outb_p(VGA_CRTC_MODE, vga_video_port_reg);
		mode = inb_p(vga_video_port_val);

		if (mode & 0x04)
			scanlines >>= 1;

		scanlines -= 1;
		scanlines_lo = scanlines & 0xff;

		outb_p(VGA_CRTC_OVERFLOW, vga_video_port_reg);
		r7 = inb_p(vga_video_port_val) & ~0x42;

		if (scanlines & 0x100)
			r7 |= 0x02;
		if (scanlines & 0x200)
			r7 |= 0x40;

		/* deprotect registers */
		outb_p(VGA_CRTC_V_SYNC_END, vga_video_port_reg);
		vsync_end = inb_p(vga_video_port_val);
		outb_p(VGA_CRTC_V_SYNC_END, vga_video_port_reg);
		outb_p(vsync_end & ~0x80, vga_video_port_val);
	}

	outb_p(VGA_CRTC_H_DISP, vga_video_port_reg);
	outb_p(width - 1, vga_video_port_val);
	outb_p(VGA_CRTC_OFFSET, vga_video_port_reg);
	outb_p(width >> 1, vga_video_port_val);

	if (vga_video_type >= VIDEO_TYPE_VGAC) {
		outb_p(VGA_CRTC_V_DISP_END, vga_video_port_reg);
		outb_p(scanlines_lo, vga_video_port_val);
		outb_p(VGA_CRTC_OVERFLOW, vga_video_port_reg);
		outb_p(r7,vga_video_port_val);

		/* reprotect registers */
		outb_p(VGA_CRTC_V_SYNC_END, vga_video_port_reg);
		outb_p(vsync_end, vga_video_port_val);
	}

	spin_unlock_irqrestore(&vga_lock, flags);
	return 0;
}