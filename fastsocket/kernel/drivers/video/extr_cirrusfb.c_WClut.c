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
struct cirrusfb_info {scalar_t__ btype; int /*<<< orphan*/  regbase; } ;

/* Variables and functions */
 scalar_t__ BT_ALPINE ; 
 scalar_t__ BT_GD5480 ; 
 scalar_t__ BT_PICASSO ; 
 scalar_t__ BT_PICASSO4 ; 
 scalar_t__ BT_SD64 ; 
 unsigned int VGA_PEL_D ; 
 unsigned int VGA_PEL_IW ; 
 scalar_t__ is_laguna (struct cirrusfb_info*) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,unsigned int,unsigned char) ; 

__attribute__((used)) static void WClut(struct cirrusfb_info *cinfo, unsigned char regnum, unsigned char red,
	    unsigned char green, unsigned char blue)
{
	unsigned int data = VGA_PEL_D;

	/* address write mode register is not translated.. */
	vga_w(cinfo->regbase, VGA_PEL_IW, regnum);

	if (cinfo->btype == BT_PICASSO || cinfo->btype == BT_PICASSO4 ||
	    cinfo->btype == BT_ALPINE || cinfo->btype == BT_GD5480 ||
	    cinfo->btype == BT_SD64 || is_laguna(cinfo)) {
		/* but DAC data register IS, at least for Picasso II */
		if (cinfo->btype == BT_PICASSO)
			data += 0xfff;
		vga_w(cinfo->regbase, data, red);
		vga_w(cinfo->regbase, data, green);
		vga_w(cinfo->regbase, data, blue);
	} else {
		vga_w(cinfo->regbase, data, blue);
		vga_w(cinfo->regbase, data, green);
		vga_w(cinfo->regbase, data, red);
	}
}