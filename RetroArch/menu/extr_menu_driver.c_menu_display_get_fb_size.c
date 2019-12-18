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
 unsigned int menu_display_framebuf_height ; 
 size_t menu_display_framebuf_pitch ; 
 unsigned int menu_display_framebuf_width ; 

void menu_display_get_fb_size(unsigned *fb_width,
      unsigned *fb_height, size_t *fb_pitch)
{
   *fb_width  = menu_display_framebuf_width;
   *fb_height = menu_display_framebuf_height;
   *fb_pitch  = menu_display_framebuf_pitch;
}