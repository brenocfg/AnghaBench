#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  list_highlighted_background; } ;
struct TYPE_8__ {scalar_t__ x; unsigned int y; scalar_t__ press_duration; int /*<<< orphan*/  dragged; scalar_t__ pressed; } ;
struct TYPE_7__ {int /*<<< orphan*/  dragged; } ;
struct TYPE_10__ {size_t touch_feedback_selection; scalar_t__ landscape_entry_margin; unsigned int nav_bar_layout_width; unsigned int nav_bar_layout_height; float touch_feedback_alpha; int transition_alpha; TYPE_3__ colors; TYPE_2__ pointer; TYPE_1__ scrollbar; } ;
typedef  TYPE_4__ materialui_handle_t ;
typedef  int /*<<< orphan*/  higlight_color ;

/* Variables and functions */
 scalar_t__ MENU_INPUT_PRESS_TIME_SHORT ; 
 int /*<<< orphan*/  materialui_render_selection_highlight (TYPE_4__*,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,int,size_t,float*) ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ ,int) ; 
 float menu_animation_get_delta_time () ; 
 int /*<<< orphan*/  menu_display_set_alpha (float*,int) ; 
 size_t menu_input_get_pointer_selection () ; 

__attribute__((used)) static void materialui_render_entry_touch_feedback(
      materialui_handle_t *mui, video_frame_info_t *video_info,
      unsigned width, unsigned height, unsigned header_height, int x_offset,
      size_t current_selection)
{
   /* Check whether pointer is currently
    * held and stationary */
   bool pointer_active =
         (!mui->scrollbar.dragged &&
          mui->pointer.pressed &&
          !mui->pointer.dragged);

   /* If pointer is held and stationary, need to check
    * that current pointer selection is valid
    * i.e. user may be touching the header/navigation bar,
    * or pointer may no longer be held above the entry
    * currently selected for feedback animations */
   if (pointer_active)
      pointer_active = (mui->touch_feedback_selection == menu_input_get_pointer_selection()) &&
                       (mui->pointer.x >  mui->landscape_entry_margin) &&
                       (mui->pointer.x <  width - mui->landscape_entry_margin - mui->nav_bar_layout_width) &&
                       (mui->pointer.y >= header_height) &&
                       (mui->pointer.y <= height - mui->nav_bar_layout_height);

   /* Touch feedback highlight fades in when pointer
    * is held stationary on a menu entry */
   if (pointer_active)
   {
      /* If pointer is held on currently selected item,
       * background highlight is already drawn
       * > Feedback animation is over, so reset
       *   alpha value and draw nothing */
      if (mui->touch_feedback_selection == current_selection)
      {
         mui->touch_feedback_alpha = 0.0f;
         return;
      }

      /* Update highlight opacity */
      mui->touch_feedback_alpha = (float)mui->pointer.press_duration / (float)MENU_INPUT_PRESS_TIME_SHORT;
      mui->touch_feedback_alpha = (mui->touch_feedback_alpha > 1.0f) ? 1.0f : mui->touch_feedback_alpha;
   }
   /* If pointer has moved, or has been released, any
    * unfinished feedback highlight animation must
    * fade out */
   else if (mui->touch_feedback_alpha > 0.0f)
   {
      mui->touch_feedback_alpha -= (menu_animation_get_delta_time() * 1000.0f) / (float)MENU_INPUT_PRESS_TIME_SHORT;
      mui->touch_feedback_alpha = (mui->touch_feedback_alpha < 0.0f) ? 0.0f : mui->touch_feedback_alpha;
   }

   /* If alpha value is greater than zero, draw
    * touch feedback highlight */
   if (mui->touch_feedback_alpha > 0.0f)
   {
      float higlight_color[16];

      /* Set highlight colour */
      memcpy(higlight_color, mui->colors.list_highlighted_background, sizeof(higlight_color));
      menu_display_set_alpha(higlight_color, mui->transition_alpha * mui->touch_feedback_alpha);

      /* Draw highlight */
      materialui_render_selection_highlight(
            mui, video_info, width, height, header_height, x_offset,
            mui->touch_feedback_selection,
            higlight_color);
   }
}