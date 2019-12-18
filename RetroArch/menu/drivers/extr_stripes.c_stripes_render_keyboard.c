#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned int width; unsigned int height; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct TYPE_11__ {uintptr_t* list; } ;
struct TYPE_13__ {TYPE_7__* font; TYPE_1__ textures; } ;
typedef  TYPE_3__ stripes_handle_t ;
struct TYPE_14__ {int size; } ;

/* Variables and functions */
 size_t STRIPES_TEXTURE_KEY_HOVER ; 
 int /*<<< orphan*/  TEXT_ALIGN_CENTER ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_blend_end (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_draw_quad (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,float*) ; 
 int /*<<< orphan*/  menu_display_draw_text (TYPE_7__*,char*,unsigned int,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_draw_texture (TYPE_2__*,unsigned int,unsigned int,int,int,unsigned int,unsigned int,float*,uintptr_t) ; 

__attribute__((used)) static void stripes_render_keyboard(
      stripes_handle_t *stripes,
      video_frame_info_t *video_info,
      char **grid, unsigned id)
{
   unsigned i;
   int ptr_width, ptr_height;
   unsigned width    = video_info->width;
   unsigned height   = video_info->height;
   float dark[16]    =  {
      0.00, 0.00, 0.00, 0.85,
      0.00, 0.00, 0.00, 0.85,
      0.00, 0.00, 0.00, 0.85,
      0.00, 0.00, 0.00, 0.85,
   };

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
         &dark[0]);

   ptr_width  = width / 11;
   ptr_height = height / 10;

   if (ptr_width >= ptr_height)
      ptr_width = ptr_height;

   for (i = 0; i < 44; i++)
   {
      int line_y = (i / 11) * height / 10.0;

      if (i == id)
      {
         uintptr_t texture = stripes->textures.list[STRIPES_TEXTURE_KEY_HOVER];

         menu_display_blend_begin(video_info);

         menu_display_draw_texture(
               video_info,
               width/2.0 - (11*ptr_width)/2.0 + (i % 11) * ptr_width,
               height/2.0 + ptr_height*1.5 + line_y,
               ptr_width, ptr_height,
               width, height,
               &white[0],
               texture);

         menu_display_blend_end(video_info);
      }

      menu_display_draw_text(stripes->font, grid[i],
            width/2.0 - (11*ptr_width)/2.0 + (i % 11) * ptr_width + ptr_width/2.0,
            height/2.0 + ptr_height + line_y + stripes->font->size / 3,
            width, height, 0xffffffff, TEXT_ALIGN_CENTER, 1.0f,
            false, 0, false);
   }
}