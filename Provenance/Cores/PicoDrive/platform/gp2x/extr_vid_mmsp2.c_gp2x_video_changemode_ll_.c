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
 int* memregs ; 

__attribute__((used)) static void gp2x_video_changemode_ll_(int bpp, int is_pal)
{
  	memregs[0x28DA>>1] = (((bpp+1)/8)<<9)|0xAB; /*8/15/16/24bpp...*/
  	memregs[0x290C>>1] = 320*((bpp+1)/8); /*line width in bytes*/
}