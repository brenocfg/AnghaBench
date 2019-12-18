#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
struct TYPE_22__ {unsigned int height; int /*<<< orphan*/  width; } ;
typedef  TYPE_4__ video_frame_info_t ;
typedef  int /*<<< orphan*/  task_percentage ;
struct TYPE_21__ {int video_font_size; } ;
struct TYPE_23__ {TYPE_3__ floats; } ;
typedef  TYPE_5__ settings_t ;
struct TYPE_24__ {int task_progress; float width; float alpha; int task_count; unsigned int offset_y; char* msg_new; int msg_transition_animation; char* msg; int /*<<< orphan*/  hourglass_rotation; scalar_t__ task_finished; scalar_t__ task_error; } ;
typedef  TYPE_6__ menu_widget_msg_t ;
struct TYPE_19__ {scalar_t__ vertices; } ;
struct TYPE_20__ {TYPE_1__ coords; } ;
struct TYPE_18__ {TYPE_2__ carr; } ;

/* Variables and functions */
 unsigned int COLOR_TEXT_ALPHA (int,unsigned int) ; 
 size_t MENU_WIDGETS_ICON_CHECK ; 
 size_t MENU_WIDGETS_ICON_HOURGLASS ; 
 int /*<<< orphan*/  TEXT_ALIGN_LEFT ; 
 int /*<<< orphan*/  TEXT_ALIGN_RIGHT ; 
 TYPE_5__* config_get_ptr () ; 
 int /*<<< orphan*/  font_driver_flush (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_15__ font_raster_regular ; 
 int /*<<< orphan*/  font_regular ; 
 int glyph_width ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_4__*) ; 
 int /*<<< orphan*/  menu_display_blend_end (TYPE_4__*) ; 
 int /*<<< orphan*/  menu_display_draw_quad (TYPE_4__*,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,float*) ; 
 int /*<<< orphan*/  menu_display_draw_text (int /*<<< orphan*/ ,char*,scalar_t__,int,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_scissor_begin (TYPE_4__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  menu_display_scissor_end (TYPE_4__*) ; 
 int /*<<< orphan*/  menu_display_set_alpha (float*,float) ; 
 int /*<<< orphan*/  menu_widgets_draw_icon (TYPE_4__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/ * menu_widgets_icons_textures ; 
 float* menu_widgets_pure_white ; 
 float* msg_queue_background ; 
 scalar_t__ msg_queue_glyph_width ; 
 int msg_queue_height ; 
 unsigned int msg_queue_icon_size_x ; 
 unsigned int msg_queue_rect_start_x ; 
 int /*<<< orphan*/  msg_queue_task_hourglass_x ; 
 float* msg_queue_task_progress_1 ; 
 float* msg_queue_task_progress_2 ; 
 unsigned int msg_queue_task_rect_start_x ; 
 scalar_t__ msg_queue_task_text_start_x ; 
 int msg_queue_text_scale_factor ; 
 float simple_widget_padding ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static void menu_widgets_draw_task_msg(menu_widget_msg_t *msg, video_frame_info_t *video_info)
{
   unsigned text_color;
   unsigned bar_width;

   unsigned rect_x;
   unsigned rect_y;
   unsigned rect_width;
   unsigned rect_height;

   float *msg_queue_current_background;
   float *msg_queue_current_bar;

   unsigned task_percentage_offset = 0;
   char task_percentage[256]       = {0};
   settings_t *settings            = config_get_ptr();

   task_percentage_offset = glyph_width * (msg->task_error ? 12 : 5) + simple_widget_padding * 1.25f; /*11 = strlen("Task failed")+1 */

   if (msg->task_finished)
   {
      if (msg->task_error)
         strlcpy(task_percentage, "Task failed", sizeof(task_percentage));
      else
         strlcpy(task_percentage, " ", sizeof(task_percentage));
   }
   else if (msg->task_progress >= 0 && msg->task_progress <= 100)
      snprintf(task_percentage, sizeof(task_percentage),
            "%i%%", msg->task_progress);

   rect_width = simple_widget_padding + msg->width + task_percentage_offset;
   bar_width  = rect_width * msg->task_progress/100.0f;
   text_color = COLOR_TEXT_ALPHA(0xFFFFFF00, (unsigned)(msg->alpha*255.0f));

   /* Rect */
   if (msg->task_finished)
      if (msg->task_count == 1)
         msg_queue_current_background = msg_queue_task_progress_1;
      else
         msg_queue_current_background = msg_queue_task_progress_2;
   else
      if (msg->task_count == 1)
         msg_queue_current_background = msg_queue_background;
      else
         msg_queue_current_background = msg_queue_task_progress_1;

   rect_x      = msg_queue_rect_start_x - msg_queue_icon_size_x;
   rect_y      = video_info->height - msg->offset_y;
   rect_height = msg_queue_height/2;

   menu_display_set_alpha(msg_queue_current_background, msg->alpha);
   menu_display_draw_quad(video_info,
      rect_x, rect_y,
      rect_width, rect_height,
      video_info->width, video_info->height,
      msg_queue_current_background
   );

   /* Progress bar */
   if (!msg->task_finished && msg->task_progress >= 0 && msg->task_progress <= 100)
   {
      if (msg->task_count == 1)
         msg_queue_current_bar = msg_queue_task_progress_1;
      else
         msg_queue_current_bar = msg_queue_task_progress_2;

      menu_display_set_alpha(msg_queue_current_bar, 1.0f);
      menu_display_draw_quad(video_info,
         msg_queue_task_rect_start_x, video_info->height - msg->offset_y,
         bar_width, rect_height,
         video_info->width, video_info->height,
         msg_queue_current_bar
      );
   }

   /* Icon */
   menu_display_set_alpha(menu_widgets_pure_white, msg->alpha);
   menu_display_blend_begin(video_info);
   menu_widgets_draw_icon(video_info,
      msg_queue_height/2,
      msg_queue_height/2,
      menu_widgets_icons_textures[msg->task_finished ? MENU_WIDGETS_ICON_CHECK : MENU_WIDGETS_ICON_HOURGLASS],
      msg_queue_task_hourglass_x,
      video_info->height - msg->offset_y,
      video_info->width,
      video_info->height,
      msg->task_finished ? 0 : msg->hourglass_rotation,
      1, menu_widgets_pure_white);
   menu_display_blend_end(video_info);

   /* Text */
   if (msg->msg_new)
   {
      font_driver_flush(video_info->width, video_info->height, font_regular, video_info);
      font_raster_regular.carr.coords.vertices  = 0;

      menu_display_scissor_begin(video_info, rect_x, rect_y, rect_width, rect_height);
      menu_display_draw_text(font_regular,
         msg->msg_new,
         msg_queue_task_text_start_x,
         video_info->height - msg->offset_y + msg_queue_text_scale_factor * settings->floats.video_font_size + msg_queue_height/4 - settings->floats.video_font_size/2.25f - msg_queue_height/2 + msg->msg_transition_animation,
         video_info->width, video_info->height,
         text_color,
         TEXT_ALIGN_LEFT,
         msg_queue_text_scale_factor,
         false,
         0,
         true
      );
   }

   menu_display_draw_text(font_regular,
      msg->msg,
      msg_queue_task_text_start_x,
      video_info->height - msg->offset_y + msg_queue_text_scale_factor * settings->floats.video_font_size + msg_queue_height/4 - settings->floats.video_font_size/2.25f + msg->msg_transition_animation,
      video_info->width, video_info->height,
      text_color,
      TEXT_ALIGN_LEFT,
      msg_queue_text_scale_factor,
      false,
      0,
      true
   );

   if (msg->msg_new)
   {
      font_driver_flush(video_info->width, video_info->height, font_regular, video_info);
      font_raster_regular.carr.coords.vertices  = 0;

      menu_display_scissor_end(video_info);
   }

   /* Progress text */
   text_color = COLOR_TEXT_ALPHA(0xFFFFFF00, (unsigned)(msg->alpha/2*255.0f));
   menu_display_draw_text(font_regular,
      task_percentage,
      msg_queue_rect_start_x - msg_queue_icon_size_x + rect_width - msg_queue_glyph_width,
      video_info->height - msg->offset_y + msg_queue_text_scale_factor * settings->floats.video_font_size + msg_queue_height/4 - settings->floats.video_font_size/2.25f,
      video_info->width, video_info->height,
      text_color,
      TEXT_ALIGN_RIGHT,
      msg_queue_text_scale_factor,
      false,
      0,
      true
   );
}