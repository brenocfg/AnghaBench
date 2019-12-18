#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t menu_animation_ctx_tag ;
struct TYPE_5__ {uintptr_t tag; float duration; float target_value; int /*<<< orphan*/ * userdata; int /*<<< orphan*/ * cb; int /*<<< orphan*/ * subject; int /*<<< orphan*/  easing_enum; } ;
typedef  TYPE_1__ menu_animation_ctx_entry_t ;
struct TYPE_6__ {int /*<<< orphan*/  scroll_y; } ;
typedef  TYPE_2__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_IN_OUT_QUAD ; 
 int /*<<< orphan*/  menu_animation_kill_by_tag (uintptr_t*) ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_input_set_pointer_y_accel (float) ; 

__attribute__((used)) static void materialui_animate_scroll(
      materialui_handle_t *mui, float scroll_pos, float duration)
{
   menu_animation_ctx_tag animation_tag = (uintptr_t)&mui->scroll_y;
   menu_animation_ctx_entry_t animation_entry;

   /* Kill any existing scroll animation */
   menu_animation_kill_by_tag(&animation_tag);

   /* mui->scroll_y will be modified by the animation
    * > Set scroll acceleration to zero to minimise
    *   potential conflicts */
   menu_input_set_pointer_y_accel(0.0f);

   /* Configure animation */
   animation_entry.easing_enum  = EASING_IN_OUT_QUAD;
   animation_entry.tag          = animation_tag;
   animation_entry.duration     = duration;
   animation_entry.target_value = scroll_pos;
   animation_entry.subject      = &mui->scroll_y;
   animation_entry.cb           = NULL;
   animation_entry.userdata     = NULL;

   /* Push animation */
   menu_animation_push(&animation_entry);
}