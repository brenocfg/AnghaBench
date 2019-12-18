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
struct tdfx_par {int dummy; } ;
struct fb_info {struct tdfx_par* par; } ;
struct banshee_reg {int vgainit1; int vidcfg; int mempll; int gfxpll; int vidpll; int* misc; int* crt; int* ext; int vgainit0; int dacmode; int stride; int curspataddr; int screensize; int startaddr; int miscinit0; int /*<<< orphan*/ * att; int /*<<< orphan*/ * gra; int /*<<< orphan*/ * seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP0MAX ; 
 int /*<<< orphan*/  CLIP0MIN ; 
 int /*<<< orphan*/  CLIP1MAX ; 
 int /*<<< orphan*/  CLIP1MIN ; 
 int /*<<< orphan*/  COMMANDEXTRA_2D ; 
 int /*<<< orphan*/  DACMODE ; 
 int /*<<< orphan*/  DSTBASE ; 
 int /*<<< orphan*/  HWCURPATADDR ; 
 int /*<<< orphan*/  MISCINIT0 ; 
 int /*<<< orphan*/  MISCINIT1 ; 
 int /*<<< orphan*/  MISC_W ; 
 int /*<<< orphan*/  PLLCTRL0 ; 
 int /*<<< orphan*/  PLLCTRL1 ; 
 int /*<<< orphan*/  PLLCTRL2 ; 
 int /*<<< orphan*/  SRCBASE ; 
 int /*<<< orphan*/  SRCXY ; 
 int /*<<< orphan*/  VGAINIT0 ; 
 int /*<<< orphan*/  VGAINIT1 ; 
 int /*<<< orphan*/  VIDDESKSTART ; 
 int /*<<< orphan*/  VIDDESKSTRIDE ; 
 int /*<<< orphan*/  VIDPROCCFG ; 
 int /*<<< orphan*/  VIDSCREENSIZE ; 
 int /*<<< orphan*/  att_outb (struct tdfx_par*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banshee_make_room (struct tdfx_par*,int) ; 
 int /*<<< orphan*/  banshee_wait_idle (struct fb_info*) ; 
 int crt_inb (struct tdfx_par*,int) ; 
 int /*<<< orphan*/  crt_outb (struct tdfx_par*,int,int) ; 
 int /*<<< orphan*/  gra_outb (struct tdfx_par*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_outb (struct tdfx_par*,int,int /*<<< orphan*/ ) ; 
 int tdfx_inl (struct tdfx_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdfx_outl (struct tdfx_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_enable_palette (struct tdfx_par*) ; 
 int /*<<< orphan*/  vga_enable_video (struct tdfx_par*) ; 
 int /*<<< orphan*/  vga_outb (struct tdfx_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_write_regs(struct fb_info *info, struct banshee_reg *reg)
{
	struct tdfx_par *par = info->par;
	int i;

	banshee_wait_idle(info);

	tdfx_outl(par, MISCINIT1, tdfx_inl(par, MISCINIT1) | 0x01);

	crt_outb(par, 0x11, crt_inb(par, 0x11) & 0x7f); /* CRT unprotect */

	banshee_make_room(par, 3);
	tdfx_outl(par, VGAINIT1, reg->vgainit1 & 0x001FFFFF);
	tdfx_outl(par, VIDPROCCFG, reg->vidcfg & ~0x00000001);
#if 0
	tdfx_outl(par, PLLCTRL1, reg->mempll);
	tdfx_outl(par, PLLCTRL2, reg->gfxpll);
#endif
	tdfx_outl(par, PLLCTRL0, reg->vidpll);

	vga_outb(par, MISC_W, reg->misc[0x00] | 0x01);

	for (i = 0; i < 5; i++)
		seq_outb(par, i, reg->seq[i]);

	for (i = 0; i < 25; i++)
		crt_outb(par, i, reg->crt[i]);

	for (i = 0; i < 9; i++)
		gra_outb(par, i, reg->gra[i]);

	for (i = 0; i < 21; i++)
		att_outb(par, i, reg->att[i]);

	crt_outb(par, 0x1a, reg->ext[0]);
	crt_outb(par, 0x1b, reg->ext[1]);

	vga_enable_palette(par);
	vga_enable_video(par);

	banshee_make_room(par, 9);
	tdfx_outl(par, VGAINIT0, reg->vgainit0);
	tdfx_outl(par, DACMODE, reg->dacmode);
	tdfx_outl(par, VIDDESKSTRIDE, reg->stride);
	tdfx_outl(par, HWCURPATADDR, reg->curspataddr);

	tdfx_outl(par, VIDSCREENSIZE, reg->screensize);
	tdfx_outl(par, VIDDESKSTART, reg->startaddr);
	tdfx_outl(par, VIDPROCCFG, reg->vidcfg);
	tdfx_outl(par, VGAINIT1, reg->vgainit1);
	tdfx_outl(par, MISCINIT0, reg->miscinit0);

	banshee_make_room(par, 8);
	tdfx_outl(par, SRCBASE, reg->startaddr);
	tdfx_outl(par, DSTBASE, reg->startaddr);
	tdfx_outl(par, COMMANDEXTRA_2D, 0);
	tdfx_outl(par, CLIP0MIN, 0);
	tdfx_outl(par, CLIP0MAX, 0x0fff0fff);
	tdfx_outl(par, CLIP1MIN, 0);
	tdfx_outl(par, CLIP1MAX, 0x0fff0fff);
	tdfx_outl(par, SRCXY, 0);

	banshee_wait_idle(info);
}