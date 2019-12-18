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
typedef  uintptr_t menu_animation_ctx_tag ;
struct TYPE_3__ {uintptr_t tag; float target_value; int /*<<< orphan*/ * userdata; int /*<<< orphan*/ * subject; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; int /*<<< orphan*/ * cb; } ;
typedef  TYPE_1__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MSG_QUEUE_ANIMATION_DURATION ; 
 int /*<<< orphan*/  libretro_message_alpha ; 
 int /*<<< orphan*/  libretro_message_timer ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_1__*) ; 

__attribute__((used)) static void menu_widgets_libretro_message_fadeout(void *userdata)
{
   menu_animation_ctx_tag tag = (uintptr_t) &libretro_message_timer;
   menu_animation_ctx_entry_t entry;

   /* Start fade out animation */
   entry.cb             = NULL;
   entry.duration       = MSG_QUEUE_ANIMATION_DURATION;
   entry.easing_enum    = EASING_OUT_QUAD;
   entry.subject        = &libretro_message_alpha;
   entry.tag            = tag;
   entry.target_value   = 0.0f;
   entry.userdata       = NULL;

   menu_animation_push(&entry);
}