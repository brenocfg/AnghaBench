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
struct TYPE_4__ {float hourglass_rotation; int /*<<< orphan*/  hourglass_timer; } ;
typedef  TYPE_1__ menu_widget_msg_t ;
struct TYPE_5__ {TYPE_1__* userdata; int /*<<< orphan*/  duration; int /*<<< orphan*/  cb; } ;
typedef  TYPE_2__ menu_timer_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOURGLASS_INTERVAL ; 
 int /*<<< orphan*/  menu_timer_start (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_widgets_hourglass_tick ; 

__attribute__((used)) static void menu_widgets_hourglass_end(void *userdata)
{
   menu_timer_ctx_entry_t timer;
   menu_widget_msg_t *msg  = (menu_widget_msg_t*) userdata;

   msg->hourglass_rotation = 0.0f;

   timer.cb                = menu_widgets_hourglass_tick;
   timer.duration          = HOURGLASS_INTERVAL;
   timer.userdata          = msg;

   menu_timer_start(&msg->hourglass_timer, &timer);
}