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
 unsigned int* clear_color ; 
 unsigned int clear_color_u ; 

void vita2d_set_clear_color(unsigned int color)
{
	clear_color[0] = ((color >> 8*0) & 0xFF)/255.0f;
	clear_color[1] = ((color >> 8*1) & 0xFF)/255.0f;
	clear_color[2] = ((color >> 8*2) & 0xFF)/255.0f;
	clear_color[3] = ((color >> 8*3) & 0xFF)/255.0f;
	clear_color_u = color;
}