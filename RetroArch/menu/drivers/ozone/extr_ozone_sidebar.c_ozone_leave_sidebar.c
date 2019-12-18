#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct menu_animation_ctx_entry {float* subject; uintptr_t tag; float target_value; int /*<<< orphan*/ * userdata; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; int /*<<< orphan*/ * cb; } ;
struct TYPE_6__ {float cursor_alpha; } ;
struct TYPE_7__ {int cursor_in_sidebar_old; int cursor_in_sidebar; TYPE_1__ animations; int /*<<< orphan*/  categories_selection_ptr; int /*<<< orphan*/  categories_active_idx_old; scalar_t__ empty_playlist; } ;
typedef  TYPE_2__ ozone_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ANIMATION_CURSOR_DURATION ; 
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  menu_animation_push (struct menu_animation_ctx_entry*) ; 
 int /*<<< orphan*/  ozone_sidebar_update_collapse (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ozone_update_content_metadata (TYPE_2__*) ; 

void ozone_leave_sidebar(ozone_handle_t *ozone, uintptr_t tag)
{
   struct menu_animation_ctx_entry entry;

   if (ozone->empty_playlist)
      return;

   ozone_update_content_metadata(ozone);

   ozone->categories_active_idx_old = ozone->categories_selection_ptr;
   ozone->cursor_in_sidebar_old     = ozone->cursor_in_sidebar;
   ozone->cursor_in_sidebar         = false;

   /* Cursor animation */
   ozone->animations.cursor_alpha   = 0.0f;

   entry.cb             = NULL;
   entry.duration       = ANIMATION_CURSOR_DURATION;
   entry.easing_enum    = EASING_OUT_QUAD;
   entry.subject        = &ozone->animations.cursor_alpha;
   entry.tag            = tag;
   entry.target_value   = 1.0f;
   entry.userdata       = NULL;

   menu_animation_push(&entry);

   ozone_sidebar_update_collapse(ozone, true);
}