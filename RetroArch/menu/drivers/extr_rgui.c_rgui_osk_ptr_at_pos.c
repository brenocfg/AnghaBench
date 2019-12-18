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
 unsigned int FONT_HEIGHT ; 
 int FONT_HEIGHT_STRIDE ; 
 unsigned int FONT_WIDTH ; 
 unsigned int OSK_CHARS_PER_LINE ; 
 int /*<<< orphan*/  menu_display_get_fb_size (unsigned int*,unsigned int*,size_t*) ; 

int rgui_osk_ptr_at_pos(void *data, int x, int y,
      unsigned width, unsigned height)
{
   /* This is a lazy copy/paste from rgui_render_osk(),
    * but it will do for now... */
   size_t fb_pitch;
   unsigned fb_width, fb_height;
   size_t key_index;
   
   unsigned key_width, key_height;
   unsigned key_text_offset_x, key_text_offset_y;
   unsigned ptr_width, ptr_height;
   unsigned ptr_offset_x, ptr_offset_y;
   
   unsigned keyboard_width, keyboard_height;
   unsigned keyboard_offset_x, keyboard_offset_y;
   
   unsigned osk_width, osk_height;
   unsigned osk_x, osk_y;

   /* Get dimensions/layout */
   menu_display_get_fb_size(&fb_width, &fb_height, &fb_pitch);

   key_text_offset_x      = 8;
   key_text_offset_y      = 6;
   key_width              = FONT_WIDTH  + (key_text_offset_x * 2);
   key_height             = FONT_HEIGHT + (key_text_offset_y * 2);
   ptr_offset_x           = 2;
   ptr_offset_y           = 2;
   ptr_width              = key_width  - (ptr_offset_x * 2);
   ptr_height             = key_height - (ptr_offset_y * 2);
   keyboard_width         = key_width  * OSK_CHARS_PER_LINE;
   keyboard_height        = key_height * 4;
   keyboard_offset_x      = 10;
   keyboard_offset_y      = 10 + 15 + (2 * FONT_HEIGHT_STRIDE);
   osk_width              = keyboard_width + 20;
   osk_height             = keyboard_offset_y + keyboard_height + 10;
   osk_x                  = (fb_width - osk_width) / 2;
   osk_y                  = (fb_height - osk_height) / 2;

   for (key_index = 0; key_index < 44; key_index++)
   {
      unsigned key_row     = (unsigned)(key_index / OSK_CHARS_PER_LINE);
      unsigned key_column  = (unsigned)(key_index - (key_row * OSK_CHARS_PER_LINE));

      unsigned osk_ptr_x = osk_x + keyboard_offset_x + ptr_offset_x + (key_column * key_width);
      unsigned osk_ptr_y = osk_y + keyboard_offset_y + ptr_offset_y + (key_row    * key_height);

      if (x > osk_ptr_x && x < osk_ptr_x + ptr_width &&
          y > osk_ptr_y && y < osk_ptr_y + ptr_height)
         return (int)key_index;
   }

   return -1;
}