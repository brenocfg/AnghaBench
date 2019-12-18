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
struct TYPE_4__ {int unfolded; int unfolding; int /*<<< orphan*/  unfold; } ;
typedef  TYPE_1__ menu_widget_msg_t ;
struct TYPE_5__ {uintptr_t tag; float target_value; TYPE_1__* userdata; int /*<<< orphan*/ * subject; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; int /*<<< orphan*/  cb; } ;
typedef  TYPE_2__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MSG_QUEUE_ANIMATION_DURATION ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_widgets_unfold_end ; 
 int widgets_moving ; 

__attribute__((used)) static void menu_widgets_move_end(void *userdata)
{
   if (userdata)
   {
      menu_widget_msg_t *unfold = (menu_widget_msg_t*) userdata;

      menu_animation_ctx_entry_t entry;

      entry.cb             = menu_widgets_unfold_end;
      entry.duration       = MSG_QUEUE_ANIMATION_DURATION;
      entry.easing_enum    = EASING_OUT_QUAD;
      entry.subject        = &unfold->unfold;
      entry.tag            = (uintptr_t) unfold;
      entry.target_value   = 1.0f;
      entry.userdata       = unfold;

      menu_animation_push(&entry);

      unfold->unfolded  = true;
      unfold->unfolding = true;
   }
   else
      widgets_moving = false;
}