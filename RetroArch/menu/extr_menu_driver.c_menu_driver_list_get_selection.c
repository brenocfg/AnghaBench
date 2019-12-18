#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ selection; } ;
typedef  TYPE_1__ menu_ctx_list_t ;
struct TYPE_5__ {scalar_t__ (* list_get_selection ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_userdata ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

bool menu_driver_list_get_selection(menu_ctx_list_t *list)
{
   if (!menu_driver_ctx || !menu_driver_ctx->list_get_selection)
   {
      list->selection = 0;
      return false;
   }
   list->selection = menu_driver_ctx->list_get_selection(menu_userdata);

   return true;
}