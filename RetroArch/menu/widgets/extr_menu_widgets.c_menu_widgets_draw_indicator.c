#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct TYPE_10__ {scalar_t__ video_font_size; } ;
struct TYPE_12__ {TYPE_1__ floats; } ;
typedef  TYPE_3__ settings_t ;
typedef  scalar_t__ menu_texture_item ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
 float DEFAULT_BACKDROP ; 
 int /*<<< orphan*/  TEXT_ALIGN_LEFT ; 
 TYPE_3__* config_get_ptr () ; 
 int font_driver_get_message_width (int /*<<< orphan*/ ,char const*,unsigned int,int) ; 
 int /*<<< orphan*/  font_regular ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_blend_end (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_draw_quad (TYPE_2__*,int,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_draw_text (int /*<<< orphan*/ ,char const*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_set_alpha (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  menu_widgets_backdrop_orig ; 
 int /*<<< orphan*/  menu_widgets_draw_icon (TYPE_2__*,unsigned int,unsigned int,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_widgets_pure_white ; 
 char* msg_hash_to_str (int) ; 
 int simple_widget_height ; 
 int simple_widget_padding ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int menu_widgets_draw_indicator(video_frame_info_t *video_info, 
      menu_texture_item icon, int y, int top_right_x_advance, 
      enum msg_hash_enums msg)
{
   unsigned width;
   settings_t *settings = config_get_ptr();

   menu_display_set_alpha(menu_widgets_backdrop_orig, DEFAULT_BACKDROP);

   if (icon)
   {
      unsigned height = simple_widget_height * 2;
      width  = height;

      menu_display_draw_quad(video_info,
         top_right_x_advance - width, y,
         width, height,
         video_info->width, video_info->height,
         menu_widgets_backdrop_orig
      );

      menu_display_set_alpha(menu_widgets_pure_white, 1.0f);

      menu_display_blend_begin(video_info);
      menu_widgets_draw_icon(video_info, width, height,
         icon, top_right_x_advance - width, y,
         video_info->width, video_info->height,
         0, 1, menu_widgets_pure_white
      );
      menu_display_blend_end(video_info);
   }
   else
   {
      unsigned height = simple_widget_height;
      const char *txt = msg_hash_to_str(msg);
      width = font_driver_get_message_width(font_regular, txt, (unsigned)strlen(txt), 1) + simple_widget_padding*2;

      menu_display_draw_quad(video_info,
         top_right_x_advance - width, y,
         width, height,
         video_info->width, video_info->height,
         menu_widgets_backdrop_orig
      );

      menu_display_draw_text(font_regular,
         txt,
         top_right_x_advance - width + simple_widget_padding, settings->floats.video_font_size + simple_widget_padding/4,
         video_info->width, video_info->height,
         0xFFFFFFFF, TEXT_ALIGN_LEFT,
         1.0f,
         false, 0, false
      );
   }

   return width;
}