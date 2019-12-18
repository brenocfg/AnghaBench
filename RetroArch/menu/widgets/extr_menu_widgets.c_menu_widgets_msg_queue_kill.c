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
struct TYPE_4__ {int dying; float offset_y; float alpha; } ;
typedef  TYPE_1__ menu_widget_msg_t ;
struct TYPE_5__ {uintptr_t tag; float* subject; float target_value; int /*<<< orphan*/ * cb; int /*<<< orphan*/ * userdata; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; } ;
typedef  TYPE_2__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MSG_QUEUE_ANIMATION_DURATION ; 
 int /*<<< orphan*/  current_msgs ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_2__*) ; 
 int /*<<< orphan*/ * menu_widgets_msg_queue_kill_end ; 
 int /*<<< orphan*/  menu_widgets_msg_queue_move () ; 
 int msg_queue_height ; 
 unsigned int msg_queue_kill ; 
 int widgets_moving ; 

__attribute__((used)) static void menu_widgets_msg_queue_kill(unsigned idx)
{
   menu_animation_ctx_entry_t entry;

   menu_widget_msg_t *msg = (menu_widget_msg_t*)
      file_list_get_userdata_at_offset(current_msgs, idx);

   if (!msg)
      return;

   widgets_moving = true;
   msg->dying     = true;

   msg_queue_kill = idx;

   /* Drop down */
   entry.cb             = NULL;
   entry.duration       = MSG_QUEUE_ANIMATION_DURATION;
   entry.easing_enum    = EASING_OUT_QUAD;
   entry.tag            = (uintptr_t) msg;
   entry.userdata       = NULL;
   entry.subject        = &msg->offset_y;
   entry.target_value   = msg->offset_y - msg_queue_height/4;

   menu_animation_push(&entry);

   /* Fade out */
   entry.cb             = menu_widgets_msg_queue_kill_end;
   entry.subject        = &msg->alpha;
   entry.target_value   = 0.0f;

   menu_animation_push(&entry);

   /* Move all messages back to their correct position */
   menu_widgets_msg_queue_move();
}