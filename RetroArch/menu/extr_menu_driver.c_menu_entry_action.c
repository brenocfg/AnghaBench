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
typedef  int /*<<< orphan*/  menu_entry_t ;
typedef  enum menu_action { ____Placeholder_menu_action } menu_action ;
struct TYPE_2__ {int (* entry_action ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ;} ;

/* Variables and functions */
 TYPE_1__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_userdata ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 

int menu_entry_action(
      menu_entry_t *entry, size_t i, enum menu_action action)
{
   if (menu_driver_ctx && menu_driver_ctx->entry_action)
      return menu_driver_ctx->entry_action(
            menu_userdata, entry, i, action);
   return -1;
}