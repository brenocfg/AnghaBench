#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float target_value; int /*<<< orphan*/ * subject; int /*<<< orphan*/ * userdata; int /*<<< orphan*/  tag; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; int /*<<< orphan*/ * cb; } ;
typedef  TYPE_1__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MSG_QUEUE_ANIMATION_DURATION ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_1__*) ; 
 int /*<<< orphan*/  volume_alpha ; 
 int /*<<< orphan*/  volume_tag ; 
 int /*<<< orphan*/  volume_text_alpha ; 

__attribute__((used)) static void menu_widgets_volume_timer_end(void *userdata)
{
   menu_animation_ctx_entry_t entry;

   entry.cb             = NULL;
   entry.duration       = MSG_QUEUE_ANIMATION_DURATION;
   entry.easing_enum    = EASING_OUT_QUAD;
   entry.subject        = &volume_alpha;
   entry.tag            = volume_tag;
   entry.target_value   = 0.0f;
   entry.userdata       = NULL;

   menu_animation_push(&entry);

   entry.subject        = &volume_text_alpha;

   menu_animation_push(&entry);
}