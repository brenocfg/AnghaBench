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
struct neofb_par {int MiscOutReg; int* Sequencer; int* CRTC; int* Graphics; int* Attribute; } ;
struct fb_var_screeninfo {int xres; int right_margin; int hsync_len; int left_margin; int yres; int lower_margin; int vsync_len; int upper_margin; int sync; int vmode; int xres_virtual; } ;

/* Variables and functions */
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_DOUBLE ; 

__attribute__((used)) static int vgaHWInit(const struct fb_var_screeninfo *var,
		     struct neofb_par *par)
{
	int hsync_end = var->xres + var->right_margin + var->hsync_len;
	int htotal = (hsync_end + var->left_margin) >> 3;
	int vsync_start = var->yres + var->lower_margin;
	int vsync_end = vsync_start + var->vsync_len;
	int vtotal = vsync_end + var->upper_margin;

	par->MiscOutReg = 0x23;

	if (!(var->sync & FB_SYNC_HOR_HIGH_ACT))
		par->MiscOutReg |= 0x40;

	if (!(var->sync & FB_SYNC_VERT_HIGH_ACT))
		par->MiscOutReg |= 0x80;

	/*
	 * Time Sequencer
	 */
	par->Sequencer[0] = 0x00;
	par->Sequencer[1] = 0x01;
	par->Sequencer[2] = 0x0F;
	par->Sequencer[3] = 0x00;	/* Font select */
	par->Sequencer[4] = 0x0E;	/* Misc */

	/*
	 * CRTC Controller
	 */
	par->CRTC[0] = htotal - 5;
	par->CRTC[1] = (var->xres >> 3) - 1;
	par->CRTC[2] = (var->xres >> 3) - 1;
	par->CRTC[3] = ((htotal - 1) & 0x1F) | 0x80;
	par->CRTC[4] = ((var->xres + var->right_margin) >> 3);
	par->CRTC[5] = (((htotal - 1) & 0x20) << 2)
	    | (((hsync_end >> 3)) & 0x1F);
	par->CRTC[6] = (vtotal - 2) & 0xFF;
	par->CRTC[7] = (((vtotal - 2) & 0x100) >> 8)
	    | (((var->yres - 1) & 0x100) >> 7)
	    | ((vsync_start & 0x100) >> 6)
	    | (((var->yres - 1) & 0x100) >> 5)
	    | 0x10 | (((vtotal - 2) & 0x200) >> 4)
	    | (((var->yres - 1) & 0x200) >> 3)
	    | ((vsync_start & 0x200) >> 2);
	par->CRTC[8] = 0x00;
	par->CRTC[9] = (((var->yres - 1) & 0x200) >> 4) | 0x40;

	if (var->vmode & FB_VMODE_DOUBLE)
		par->CRTC[9] |= 0x80;

	par->CRTC[10] = 0x00;
	par->CRTC[11] = 0x00;
	par->CRTC[12] = 0x00;
	par->CRTC[13] = 0x00;
	par->CRTC[14] = 0x00;
	par->CRTC[15] = 0x00;
	par->CRTC[16] = vsync_start & 0xFF;
	par->CRTC[17] = (vsync_end & 0x0F) | 0x20;
	par->CRTC[18] = (var->yres - 1) & 0xFF;
	par->CRTC[19] = var->xres_virtual >> 4;
	par->CRTC[20] = 0x00;
	par->CRTC[21] = (var->yres - 1) & 0xFF;
	par->CRTC[22] = (vtotal - 1) & 0xFF;
	par->CRTC[23] = 0xC3;
	par->CRTC[24] = 0xFF;

	/*
	 * are these unnecessary?
	 * vgaHWHBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN | KGA_ENABLE_ON_ZERO);
	 * vgaHWVBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN | KGA_ENABLE_ON_ZERO);
	 */

	/*
	 * Graphics Display Controller
	 */
	par->Graphics[0] = 0x00;
	par->Graphics[1] = 0x00;
	par->Graphics[2] = 0x00;
	par->Graphics[3] = 0x00;
	par->Graphics[4] = 0x00;
	par->Graphics[5] = 0x40;
	par->Graphics[6] = 0x05;	/* only map 64k VGA memory !!!! */
	par->Graphics[7] = 0x0F;
	par->Graphics[8] = 0xFF;


	par->Attribute[0] = 0x00;	/* standard colormap translation */
	par->Attribute[1] = 0x01;
	par->Attribute[2] = 0x02;
	par->Attribute[3] = 0x03;
	par->Attribute[4] = 0x04;
	par->Attribute[5] = 0x05;
	par->Attribute[6] = 0x06;
	par->Attribute[7] = 0x07;
	par->Attribute[8] = 0x08;
	par->Attribute[9] = 0x09;
	par->Attribute[10] = 0x0A;
	par->Attribute[11] = 0x0B;
	par->Attribute[12] = 0x0C;
	par->Attribute[13] = 0x0D;
	par->Attribute[14] = 0x0E;
	par->Attribute[15] = 0x0F;
	par->Attribute[16] = 0x41;
	par->Attribute[17] = 0xFF;
	par->Attribute[18] = 0x0F;
	par->Attribute[19] = 0x00;
	par->Attribute[20] = 0x00;
	return 0;
}