#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float msg_transition_animation; int /*<<< orphan*/ * msg_new; int /*<<< orphan*/ * msg; } ;
typedef  TYPE_1__ menu_widget_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msg_widget_msg_transition_animation_done(void *userdata)
{
   menu_widget_msg_t *msg = (menu_widget_msg_t*) userdata;

   free(msg->msg);

   msg->msg                      = msg->msg_new;
   msg->msg_new                  = NULL;
   msg->msg_transition_animation = 0.0f;
}