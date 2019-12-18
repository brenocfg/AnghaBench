#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int position_y; int height; } ;
typedef  TYPE_3__ ozone_node_t ;
struct TYPE_10__ {int scroll_y; float cursor_alpha; } ;
struct TYPE_9__ {int header_height; int entry_padding_vertical; unsigned int footer_height; } ;
struct TYPE_12__ {float entries_height; TYPE_2__ animations; int /*<<< orphan*/  selection; int /*<<< orphan*/  selection_old; TYPE_1__ dimensions; } ;
typedef  TYPE_4__ ozone_handle_t ;
typedef  void* menu_animation_ctx_tag ;
struct TYPE_13__ {float* subject; float target_value; int /*<<< orphan*/ * userdata; void* tag; void* easing_enum; void* duration; int /*<<< orphan*/ * cb; } ;
typedef  TYPE_5__ menu_animation_ctx_entry_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 void* ANIMATION_CURSOR_DURATION ; 
 void* EASING_OUT_QUAD ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_5__*) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_get_size (int /*<<< orphan*/ *,unsigned int*) ; 

void ozone_update_scroll(ozone_handle_t *ozone, bool allow_animation, ozone_node_t *node)
{
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
   menu_animation_ctx_tag tag = (uintptr_t) selection_buf;
   menu_animation_ctx_entry_t entry;
   float new_scroll = 0, entries_middle;
   float bottom_boundary, current_selection_middle_onscreen;
   unsigned video_info_height;

   video_driver_get_size(NULL, &video_info_height);

   current_selection_middle_onscreen    =
      ozone->dimensions.header_height +
      ozone->dimensions.entry_padding_vertical +
      ozone->animations.scroll_y +
      node->position_y +
      node->height / 2;

   bottom_boundary                      = video_info_height - ozone->dimensions.header_height - 1 - ozone->dimensions.footer_height;
   entries_middle                       = video_info_height/2;

   new_scroll = ozone->animations.scroll_y - (current_selection_middle_onscreen - entries_middle);

   if (new_scroll + ozone->entries_height < bottom_boundary)
      new_scroll = bottom_boundary - ozone->entries_height - ozone->dimensions.entry_padding_vertical * 2;

   if (new_scroll > 0)
      new_scroll = 0;

   if (allow_animation)
   {
      /* Cursor animation */
      ozone->animations.cursor_alpha = 0.0f;

      entry.cb             = NULL;
      entry.duration       = ANIMATION_CURSOR_DURATION;
      entry.easing_enum    = EASING_OUT_QUAD;
      entry.subject        = &ozone->animations.cursor_alpha;
      entry.tag            = tag;
      entry.target_value   = 1.0f;
      entry.userdata       = NULL;

      menu_animation_push(&entry);

      /* Scroll animation */
      entry.cb             = NULL;
      entry.duration       = ANIMATION_CURSOR_DURATION;
      entry.easing_enum    = EASING_OUT_QUAD;
      entry.subject        = &ozone->animations.scroll_y;
      entry.tag            = tag;
      entry.target_value   = new_scroll;
      entry.userdata       = NULL;

      menu_animation_push(&entry);
   }
   else
   {
      ozone->selection_old = ozone->selection;
      ozone->animations.scroll_y = new_scroll;
   }
}