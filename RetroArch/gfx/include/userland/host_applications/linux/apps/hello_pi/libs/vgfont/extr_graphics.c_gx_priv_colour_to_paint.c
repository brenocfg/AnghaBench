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
typedef  int uint32_t ;
typedef  int VGfloat ;

/* Variables and functions */
 int ALPHA_888_MASK ; 
 int B_888_MASK ; 
 int G_888_MASK ; 
 int R_888_MASK ; 

void gx_priv_colour_to_paint(uint32_t col, VGfloat *rgba)
{
   // with OpenVG we use RGB order.
   rgba[0] = ((VGfloat)((col & R_888_MASK) >> 16 )) / 0xff;
   rgba[1] = ((VGfloat)((col & G_888_MASK) >> 8 )) / 0xff;
   rgba[2] = ((VGfloat)((col & B_888_MASK) >> 0 )) / 0xff;
   rgba[3] = ((VGfloat)((col & ALPHA_888_MASK) >> 24)) / 0xff;
}