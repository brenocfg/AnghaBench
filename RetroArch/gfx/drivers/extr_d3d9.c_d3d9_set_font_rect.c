#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct font_params {float x; float y; float scale; } ;
struct TYPE_8__ {float video_msg_pos_x; float video_msg_pos_y; float video_font_size; } ;
struct TYPE_11__ {TYPE_1__ floats; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_10__ {float left; float right; float top; float bottom; } ;
struct TYPE_9__ {float width; float height; } ;
struct TYPE_12__ {TYPE_3__ font_rect_shifted; TYPE_3__ font_rect; TYPE_2__ video_info; } ;
typedef  TYPE_5__ d3d9_video_t ;

/* Variables and functions */
 TYPE_4__* config_get_ptr () ; 

__attribute__((used)) static void d3d9_set_font_rect(
      d3d9_video_t *d3d,
      const struct font_params *params)
{
   settings_t *settings             = config_get_ptr();
   float pos_x                      = settings->floats.video_msg_pos_x;
   float pos_y                      = settings->floats.video_msg_pos_y;
   float font_size                  = settings->floats.video_font_size;

   if (params)
   {
      pos_x                       = params->x;
      pos_y                       = params->y;
      font_size                  *= params->scale;
   }

   if (!d3d)
      return;

   d3d->font_rect.left            = d3d->video_info.width * pos_x;
   d3d->font_rect.right           = d3d->video_info.width;
   d3d->font_rect.top             = (1.0f - pos_y) * d3d->video_info.height - font_size;
   d3d->font_rect.bottom          = d3d->video_info.height;

   d3d->font_rect_shifted         = d3d->font_rect;
   d3d->font_rect_shifted.left   -= 2;
   d3d->font_rect_shifted.right  -= 2;
   d3d->font_rect_shifted.top    += 2;
   d3d->font_rect_shifted.bottom += 2;
}