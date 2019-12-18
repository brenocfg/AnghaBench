#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int height; } ;
struct vc_data {unsigned int vc_scan_lines; TYPE_1__ vc_font; TYPE_2__* vc_sw; } ;
struct TYPE_6__ {struct vc_data* d; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* con_cursor ) (struct vc_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DRAW ; 
 scalar_t__ CON_IS_VISIBLE (struct vc_data*) ; 
 int MAX_NR_CONSOLES ; 
 scalar_t__ cursor_size_lastfrom ; 
 scalar_t__ cursor_size_lastto ; 
 unsigned char inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int /*<<< orphan*/ ) ; 
 TYPE_3__* vc_cons ; 
 int /*<<< orphan*/  vc_resize (struct vc_data*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ vga_con ; 
 int /*<<< orphan*/  vga_lock ; 
 unsigned int vga_video_font_height ; 
 int /*<<< orphan*/  vga_video_port_reg ; 
 int /*<<< orphan*/  vga_video_port_val ; 

__attribute__((used)) static int vgacon_adjust_height(struct vc_data *vc, unsigned fontheight)
{
	unsigned char ovr, vde, fsr;
	int rows, maxscan, i;

	rows = vc->vc_scan_lines / fontheight;	/* Number of video rows we end up with */
	maxscan = rows * fontheight - 1;	/* Scan lines to actually display-1 */

	/* Reprogram the CRTC for the new font size
	   Note: the attempt to read the overflow register will fail
	   on an EGA, but using 0xff for the previous value appears to
	   be OK for EGA text modes in the range 257-512 scan lines, so I
	   guess we don't need to worry about it.

	   The same applies for the spill bits in the font size and cursor
	   registers; they are write-only on EGA, but it appears that they
	   are all don't care bits on EGA, so I guess it doesn't matter. */

	spin_lock_irq(&vga_lock);
	outb_p(0x07, vga_video_port_reg);	/* CRTC overflow register */
	ovr = inb_p(vga_video_port_val);
	outb_p(0x09, vga_video_port_reg);	/* Font size register */
	fsr = inb_p(vga_video_port_val);
	spin_unlock_irq(&vga_lock);

	vde = maxscan & 0xff;	/* Vertical display end reg */
	ovr = (ovr & 0xbd) +	/* Overflow register */
	    ((maxscan & 0x100) >> 7) + ((maxscan & 0x200) >> 3);
	fsr = (fsr & 0xe0) + (fontheight - 1);	/*  Font size register */

	spin_lock_irq(&vga_lock);
	outb_p(0x07, vga_video_port_reg);	/* CRTC overflow register */
	outb_p(ovr, vga_video_port_val);
	outb_p(0x09, vga_video_port_reg);	/* Font size */
	outb_p(fsr, vga_video_port_val);
	outb_p(0x12, vga_video_port_reg);	/* Vertical display limit */
	outb_p(vde, vga_video_port_val);
	spin_unlock_irq(&vga_lock);
	vga_video_font_height = fontheight;

	for (i = 0; i < MAX_NR_CONSOLES; i++) {
		struct vc_data *c = vc_cons[i].d;

		if (c && c->vc_sw == &vga_con) {
			if (CON_IS_VISIBLE(c)) {
			        /* void size to cause regs to be rewritten */
				cursor_size_lastfrom = 0;
				cursor_size_lastto = 0;
				c->vc_sw->con_cursor(c, CM_DRAW);
			}
			c->vc_font.height = fontheight;
			vc_resize(c, 0, rows);	/* Adjust console size */
		}
	}
	return 0;
}