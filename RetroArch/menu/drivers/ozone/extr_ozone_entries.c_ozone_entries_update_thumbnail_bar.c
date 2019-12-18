#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct menu_animation_ctx_entry {uintptr_t tag; float* subject; float target_value; TYPE_3__* userdata; int /*<<< orphan*/  (* cb ) (TYPE_3__*) ;int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; } ;
struct TYPE_7__ {float thumbnail_bar_position; } ;
struct TYPE_6__ {float thumbnail_bar_width; } ;
struct TYPE_8__ {int show_thumbnail_bar; int depth; TYPE_2__ animations; TYPE_1__ dimensions; int /*<<< orphan*/  cursor_in_sidebar; } ;
typedef  TYPE_3__ ozone_handle_t ;
typedef  uintptr_t menu_animation_ctx_tag ;

/* Variables and functions */
 int /*<<< orphan*/  ANIMATION_CURSOR_DURATION ; 
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  menu_animation_kill_by_tag (uintptr_t*) ; 
 int /*<<< orphan*/  menu_animation_push (struct menu_animation_ctx_entry*) ; 
 int /*<<< orphan*/  ozone_thumbnail_bar_hide_end (TYPE_3__*) ; 

void ozone_entries_update_thumbnail_bar(ozone_handle_t *ozone, bool is_playlist, bool allow_animation)
{
   struct menu_animation_ctx_entry entry;
   menu_animation_ctx_tag tag = (uintptr_t) &ozone->show_thumbnail_bar;

   entry.duration    = ANIMATION_CURSOR_DURATION;
   entry.easing_enum = EASING_OUT_QUAD;
   entry.tag         = tag;
   entry.subject     = &ozone->animations.thumbnail_bar_position;

   menu_animation_kill_by_tag(&tag);

   /* Show it */
   if (is_playlist && !ozone->cursor_in_sidebar && !ozone->show_thumbnail_bar && ozone->depth == 1)
   {
      if (allow_animation)
      {
         ozone->show_thumbnail_bar = true;

         entry.cb             = NULL;
         entry.userdata       = NULL;
         entry.target_value   = ozone->dimensions.thumbnail_bar_width;

         menu_animation_push(&entry);
      }
      else
      {
         ozone->animations.thumbnail_bar_position = ozone->dimensions.thumbnail_bar_width;
         ozone->show_thumbnail_bar = true;
      }
   }
   /* Hide it */
   else
   {
      if (allow_animation)
      {
         entry.cb             = ozone_thumbnail_bar_hide_end;
         entry.userdata       = ozone;
         entry.target_value   = 0.0f;

         menu_animation_push(&entry);
      }
      else
      {
         ozone->animations.thumbnail_bar_position = 0.0f;
         ozone_thumbnail_bar_hide_end(ozone);
      }
   }
}