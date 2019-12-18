#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  size_t u32 ;
struct TYPE_3__ {scalar_t__ grayscale; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct pxafb_info {size_t palette_size; size_t* palette_cpu; int lccr4; TYPE_2__ fb; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
#define  LCCR4_PAL_FOR_0 131 
#define  LCCR4_PAL_FOR_1 130 
#define  LCCR4_PAL_FOR_2 129 
#define  LCCR4_PAL_FOR_3 128 
 int LCCR4_PAL_FOR_MASK ; 

__attribute__((used)) static int
pxafb_setpalettereg(u_int regno, u_int red, u_int green, u_int blue,
		       u_int trans, struct fb_info *info)
{
	struct pxafb_info *fbi = (struct pxafb_info *)info;
	u_int val;

	if (regno >= fbi->palette_size)
		return 1;

	if (fbi->fb.var.grayscale) {
		fbi->palette_cpu[regno] = ((blue >> 8) & 0x00ff);
		return 0;
	}

	switch (fbi->lccr4 & LCCR4_PAL_FOR_MASK) {
	case LCCR4_PAL_FOR_0:
		val  = ((red   >>  0) & 0xf800);
		val |= ((green >>  5) & 0x07e0);
		val |= ((blue  >> 11) & 0x001f);
		fbi->palette_cpu[regno] = val;
		break;
	case LCCR4_PAL_FOR_1:
		val  = ((red   << 8) & 0x00f80000);
		val |= ((green >> 0) & 0x0000fc00);
		val |= ((blue  >> 8) & 0x000000f8);
		((u32 *)(fbi->palette_cpu))[regno] = val;
		break;
	case LCCR4_PAL_FOR_2:
		val  = ((red   << 8) & 0x00fc0000);
		val |= ((green >> 0) & 0x0000fc00);
		val |= ((blue  >> 8) & 0x000000fc);
		((u32 *)(fbi->palette_cpu))[regno] = val;
		break;
	case LCCR4_PAL_FOR_3:
		val  = ((red   << 8) & 0x00ff0000);
		val |= ((green >> 0) & 0x0000ff00);
		val |= ((blue  >> 8) & 0x000000ff);
		((u32 *)(fbi->palette_cpu))[regno] = val;
		break;
	}

	return 0;
}