#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  menu_widget_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_msgs ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_widgets_msg_queue_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_queue_kill ; 

__attribute__((used)) static void menu_widgets_msg_queue_kill_end(void *userdata)
{
   menu_widget_msg_t *msg = (menu_widget_msg_t*)
      file_list_get_userdata_at_offset(current_msgs, msg_queue_kill);

   if (!msg)
      return;

   menu_widgets_msg_queue_free(msg, true);
}