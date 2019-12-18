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
struct cirrusfb_info {int /*<<< orphan*/  regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_CRT24 ; 
 int /*<<< orphan*/  VGA_ATT_IW ; 
 int /*<<< orphan*/  VGA_ATT_R ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int vga_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vga_rcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void AttrOn(const struct cirrusfb_info *cinfo)
{
	assert(cinfo != NULL);

	if (vga_rcrt(cinfo->regbase, CL_CRT24) & 0x80) {
		/* if we're just in "write value" mode, write back the */
		/* same value as before to not modify anything */
		vga_w(cinfo->regbase, VGA_ATT_IW,
		      vga_r(cinfo->regbase, VGA_ATT_R));
	}
	/* turn on video bit */
/*      vga_w(cinfo->regbase, VGA_ATT_IW, 0x20); */
	vga_w(cinfo->regbase, VGA_ATT_IW, 0x33);

	/* dummy write on Reg0 to be on "write index" mode next time */
	vga_w(cinfo->regbase, VGA_ATT_IW, 0x00);
}