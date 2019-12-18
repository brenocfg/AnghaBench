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
 scalar_t__* gp2x_screenaddrs ; 
 scalar_t__* gp2x_screenaddrs_use ; 
 unsigned long* memregl ; 
 int* memregs ; 

__attribute__((used)) static void gp2x_video_RGB_setscaling_(int ln_offs, int W, int H)
{
	float escalaw, escalah;
	int bpp = (memregs[0x28DA>>1]>>9)&0x3;
	unsigned short scalw;

	// set offset
	gp2x_screenaddrs_use[0] = gp2x_screenaddrs[0] + ln_offs * 320 * bpp;
	gp2x_screenaddrs_use[1] = gp2x_screenaddrs[1] + ln_offs * 320 * bpp;
	gp2x_screenaddrs_use[2] = gp2x_screenaddrs[2] + ln_offs * 320 * bpp;
	gp2x_screenaddrs_use[3] = gp2x_screenaddrs[3] + ln_offs * 320 * bpp;

	escalaw = 1024.0; // RGB Horiz LCD
	escalah = 320.0; // RGB Vert LCD

	if (memregs[0x2800>>1]&0x100) //TV-Out
	{
		escalaw=489.0; // RGB Horiz TV (PAL, NTSC)
		if (memregs[0x2818>>1]  == 287) //PAL
			escalah=274.0; // RGB Vert TV PAL
		else if (memregs[0x2818>>1]  == 239) //NTSC
			escalah=331.0; // RGB Vert TV NTSC
	}

	// scale horizontal
	scalw = (unsigned short)((float)escalaw *(W/320.0));
	/* if there is no horizontal scaling, vertical doesn't work.
	 * Here is a nasty wrokaround... */
	if (H != 240 && W == 320) scalw--;
	memregs[0x2906>>1]=scalw;
	// scale vertical
	memregl[0x2908>>2]=(unsigned long)((float)escalah *bpp *(H/240.0));
}