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
 int /*<<< orphan*/  g_screen_ptr ; 
 int* gp2x_screenaddrs_use ; 
 int /*<<< orphan*/ * gp2x_screens ; 
 unsigned short* memregs ; 
 int screensel ; 

__attribute__((used)) static void gp2x_video_flip2_(void)
{
	unsigned short msw = (unsigned short)(gp2x_screenaddrs_use[screensel&1] >> 16);

  	memregs[0x2910>>1] = msw;
  	memregs[0x2914>>1] = msw;
	memregs[0x290E>>1] = 0;
  	memregs[0x2912>>1] = 0;

	// jump to other buffer:
	g_screen_ptr = gp2x_screens[++screensel&1];
}