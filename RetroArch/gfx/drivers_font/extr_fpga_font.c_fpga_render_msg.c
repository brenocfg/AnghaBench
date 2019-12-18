#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int width; unsigned int height; float font_msg_pos_x; float font_msg_pos_y; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct font_params {float x; float y; float scale; unsigned int text_align; } ;
struct TYPE_5__ {int /*<<< orphan*/  fpga; } ;
typedef  TYPE_2__ fpga_raster_t ;

/* Variables and functions */
#define  TEXT_ALIGN_CENTER 130 
#define  TEXT_ALIGN_LEFT 129 
#define  TEXT_ALIGN_RIGHT 128 
 scalar_t__ string_is_empty (char const*) ; 
 unsigned int utf8len (char const*) ; 

__attribute__((used)) static void fpga_render_msg(
      video_frame_info_t *video_info,
      void *data, const char *msg,
      const void *userdata)
{
   float x, y, scale;
   fpga_raster_t *font = (fpga_raster_t*)data;
   unsigned newX, newY, len;
   unsigned align;
   const struct font_params *params = (const struct font_params*)userdata;
   unsigned width                   = video_info->width;
   unsigned height                  = video_info->height;

   if (!font || string_is_empty(msg))
      return;

   if (params)
   {
      x = params->x;
      y = params->y;
      scale = params->scale;
      align = params->text_align;
   }
   else
   {
      x = video_info->font_msg_pos_x;
      y = video_info->font_msg_pos_y;
      scale = 1.0f;
      align = TEXT_ALIGN_LEFT;
   }

   if (!font->fpga)
      return;

   len  = utf8len(msg);

   switch (align)
   {
      case TEXT_ALIGN_LEFT:
         newX = x * width * scale;
         break;
      case TEXT_ALIGN_RIGHT:
         newX = (x * width * scale) - len;
         break;
      case TEXT_ALIGN_CENTER:
         newX = (x * width * scale) - (len / 2);
         break;
      default:
         break;
   }

   /* TODO: draw osd msg */
}