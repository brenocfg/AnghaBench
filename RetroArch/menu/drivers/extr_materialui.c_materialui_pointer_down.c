#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;
typedef  int /*<<< orphan*/  menu_entry_t ;
typedef  uintptr_t menu_animation_ctx_tag ;
struct TYPE_3__ {int dragged; int x; int height; int y; scalar_t__ width; scalar_t__ active; } ;
struct TYPE_4__ {unsigned int pointer_start_x; unsigned int pointer_start_y; float touch_feedback_alpha; int touch_feedback_update_selection; unsigned int nav_bar_layout_height; int margin; int landscape_entry_margin; TYPE_1__ scrollbar; int /*<<< orphan*/  is_portrait; int /*<<< orphan*/  scroll_y; scalar_t__ touch_feedback_selection; int /*<<< orphan*/  pointer_start_scroll_y; } ;
typedef  TYPE_2__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MUI_THUMBNAIL_STREAM_DELAY_SCROLLBAR_DRAG ; 
 int /*<<< orphan*/  menu_animation_kill_by_tag (uintptr_t*) ; 
 unsigned int menu_display_get_header_height () ; 
 int /*<<< orphan*/  menu_input_set_pointer_y_accel (float) ; 
 int /*<<< orphan*/  menu_thumbnail_set_stream_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static int materialui_pointer_down(void *userdata,
      unsigned x, unsigned y,
      unsigned ptr, menu_file_list_cbs_t *cbs,
      menu_entry_t *entry, unsigned action)
{
   materialui_handle_t *mui = (materialui_handle_t*)userdata;

   if (!mui)
      return -1;

   /* Get initial pointer location and scroll position */
   mui->pointer_start_x        = x;
   mui->pointer_start_y        = y;
   mui->pointer_start_scroll_y = mui->scroll_y;

   /* Initialise touch feedback animation
    * > Note: ptr argument is useless here, since it
    *   has no meaning when handling touch screen input... */
   mui->touch_feedback_selection        = 0;
   mui->touch_feedback_alpha            = 0.0f;
   mui->touch_feedback_update_selection = true;

   /* Enable scrollbar dragging, if required */

   /* > Disable by default (saves checks later) */
   mui->scrollbar.dragged = false;

   /* > Check if scrollbar is enabled */
   if (mui->scrollbar.active)
   {
      unsigned header_height     = menu_display_get_header_height();
      menu_animation_ctx_tag tag = (uintptr_t)&mui->scroll_y;
      unsigned width;
      unsigned height;
      int drag_margin_horz;
      int drag_margin_vert;

      video_driver_get_size(&width, &height);

      /* Check whether pointer down event is within
       * vertical list region */
      if ((y < header_height) ||
          (y > height - mui->nav_bar_layout_height))
         return 0;

      /* Determine horizontal width of scrollbar
       * 'grab box' */
      drag_margin_horz = 2 * (int)mui->margin;
      /* > If this is a landscape layout with navigation
       *   bar on the right, and landscape optimisations
       *   are disabled (or inhibited due to insufficient
       *   screen width), need to increase 'grab box' size
       *   (otherwise the active region is too close to the
       *   navigation bar) */
      if (!mui->is_portrait)
      {
         if (mui->landscape_entry_margin <= mui->margin)
            drag_margin_horz += (int)mui->margin;
         else if (mui->landscape_entry_margin <= 2 * mui->margin)
            drag_margin_horz += (int)((2 * mui->margin) - mui->landscape_entry_margin);
      }

      /* Check whether pointer X position is within
       * scrollbar 'grab box' */
      if (((int)x < mui->scrollbar.x - drag_margin_horz) ||
          ((int)x > mui->scrollbar.x + (int)mui->scrollbar.width))
         return 0;

      /* Determine vertical height of scrollbar
       * 'grab box' */
      drag_margin_vert = 2 * (int)mui->margin;
      /* > If scrollbar is very short, increase 'grab
       *   box' size */
      if (mui->scrollbar.height < mui->margin)
         drag_margin_vert += (int)(mui->margin - mui->scrollbar.height);

      /* Check whether pointer Y position is within
       * scrollbar 'grab box' */
      if (((int)y < mui->scrollbar.y - drag_margin_vert) ||
          ((int)y > mui->scrollbar.y + (int)mui->scrollbar.height + drag_margin_vert))
         return 0;

      /* User has 'selected' scrollbar */

      /* > Kill any existing scroll animations
       *   and reset scroll acceleration */
      menu_animation_kill_by_tag(&tag);
      menu_input_set_pointer_y_accel(0.0f);

      /* > Enable dragging */
      mui->scrollbar.dragged = true;

      /* Increase thumbnail stream delay
       * (prevents overloading the system with
       * hundreds of image requests...) */
      menu_thumbnail_set_stream_delay(MUI_THUMBNAIL_STREAM_DELAY_SCROLLBAR_DRAG);
   }

   return 0;
}