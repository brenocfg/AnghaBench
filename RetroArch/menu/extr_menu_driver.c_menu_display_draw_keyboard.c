#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int width; unsigned int height; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct TYPE_11__ {int size; } ;
typedef  TYPE_2__ font_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_ALIGN_CENTER ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_display_blend_end (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_display_draw_quad (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_draw_text (TYPE_2__ const*,char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_draw_texture (TYPE_1__*,unsigned int,unsigned int,int,int,unsigned int,unsigned int,float*,uintptr_t) ; 
 int /*<<< orphan*/ * osk_dark ; 

void menu_display_draw_keyboard(
      uintptr_t hover_texture,
      const font_data_t *font,
      video_frame_info_t *video_info,
      char *grid[], unsigned id,
      unsigned text_color)
{
   unsigned i;
   int ptr_width, ptr_height;
   unsigned width    = video_info->width;
   unsigned height   = video_info->height;

   float white[16]=  {
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00,
   };

   menu_display_draw_quad(
         video_info,
         0, height/2.0, width, height/2.0,
         width, height,
         &osk_dark[0]);

   ptr_width  = width  / 11;
   ptr_height = height / 10;

   if (ptr_width >= ptr_height)
      ptr_width = ptr_height;

   for (i = 0; i < 44; i++)
   {
      int line_y     = (i / 11) * height / 10.0;
      unsigned color = 0xffffffff;

      if (i == id)
      {
         menu_display_blend_begin(video_info);

         menu_display_draw_texture(
               video_info,
               width/2.0 - (11*ptr_width)/2.0 + (i % 11) * ptr_width,
               height/2.0 + ptr_height*1.5 + line_y,
               ptr_width, ptr_height,
               width, height,
               &white[0],
               hover_texture);

         menu_display_blend_end(video_info);

         color = text_color;
      }

      menu_display_draw_text(font, grid[i],
            width/2.0 - (11*ptr_width)/2.0 + (i % 11)
            * ptr_width + ptr_width/2.0,
            height/2.0 + ptr_height + line_y + font->size / 3,
            width, height, color, TEXT_ALIGN_CENTER, 1.0f,
            false, 0, false);
   }
}