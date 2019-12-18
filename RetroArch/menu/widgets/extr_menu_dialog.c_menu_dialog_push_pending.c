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
typedef  enum menu_dialog_type { ____Placeholder_menu_dialog_type } menu_dialog_type ;

/* Variables and functions */
 int menu_dialog_active ; 
 int menu_dialog_current_type ; 
 int menu_dialog_pending_push ; 

void menu_dialog_push_pending(bool push, enum menu_dialog_type type)
{
   menu_dialog_pending_push = push;
   menu_dialog_current_type = type;
   menu_dialog_active = true;
}