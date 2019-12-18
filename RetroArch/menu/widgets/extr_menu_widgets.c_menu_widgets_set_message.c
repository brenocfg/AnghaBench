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
struct TYPE_3__ {int /*<<< orphan*/ * userdata; int /*<<< orphan*/  duration; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ menu_timer_ctx_entry_t ;
typedef  uintptr_t menu_animation_ctx_tag ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BACKDROP ; 
 int /*<<< orphan*/  GENERIC_MESSAGE_DURATION ; 
 int /*<<< orphan*/  GENERIC_MESSAGE_SIZE ; 
 int /*<<< orphan*/  generic_message ; 
 int /*<<< orphan*/  generic_message_alpha ; 
 int /*<<< orphan*/  generic_message_timer ; 
 int /*<<< orphan*/  menu_animation_kill_by_tag (uintptr_t*) ; 
 int /*<<< orphan*/  menu_timer_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_timer_start (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  menu_widgets_generic_message_fadeout ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void menu_widgets_set_message(char *msg)
{
   menu_animation_ctx_tag tag = (uintptr_t) &generic_message_timer;
   menu_timer_ctx_entry_t timer;

   strlcpy(generic_message, msg, GENERIC_MESSAGE_SIZE);

   generic_message_alpha = DEFAULT_BACKDROP;

   /* Kill and restart the timer / animation */
   menu_timer_kill(&generic_message_timer);
   menu_animation_kill_by_tag(&tag);

   timer.cb       = menu_widgets_generic_message_fadeout;
   timer.duration = GENERIC_MESSAGE_DURATION;
   timer.userdata = NULL;

   menu_timer_start(&generic_message_timer, &timer);
}