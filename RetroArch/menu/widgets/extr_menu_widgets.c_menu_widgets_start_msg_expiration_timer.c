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
struct TYPE_5__ {int expiration_timer_started; int /*<<< orphan*/  expiration_timer; } ;
typedef  TYPE_1__ menu_widget_msg_t ;
struct TYPE_6__ {unsigned int duration; TYPE_1__* userdata; int /*<<< orphan*/  cb; } ;
typedef  TYPE_2__ menu_timer_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_timer_start (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_widgets_msg_queue_expired ; 

__attribute__((used)) static void menu_widgets_start_msg_expiration_timer(menu_widget_msg_t *msg_widget, unsigned duration)
{
   menu_timer_ctx_entry_t timer;
   if (msg_widget->expiration_timer_started)
      return;

   timer.cb       = menu_widgets_msg_queue_expired;
   timer.duration = duration;
   timer.userdata = msg_widget;

   menu_timer_start(&msg_widget->expiration_timer, &timer);

   msg_widget->expiration_timer_started = true;
}