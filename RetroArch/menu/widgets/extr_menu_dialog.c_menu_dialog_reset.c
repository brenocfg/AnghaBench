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

/* Variables and functions */
 int /*<<< orphan*/  MENU_DIALOG_NONE ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 scalar_t__ menu_dialog_current_id ; 
 int /*<<< orphan*/  menu_dialog_current_msg ; 
 int /*<<< orphan*/  menu_dialog_current_type ; 
 int menu_dialog_pending_push ; 

void menu_dialog_reset(void)
{
   menu_dialog_pending_push = false;
   menu_dialog_current_id   = 0;
   menu_dialog_current_type = MENU_DIALOG_NONE;
   menu_dialog_current_msg  = MSG_UNKNOWN;
}