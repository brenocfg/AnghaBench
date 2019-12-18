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
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ menu_ctx_displaylist_t ;
struct TYPE_5__ {scalar_t__ (* list_push ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_driver_data ; 
 int /*<<< orphan*/  menu_userdata ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool menu_driver_push_list(menu_ctx_displaylist_t *disp_list)
{
   if (menu_driver_ctx->list_push)
      if (menu_driver_ctx->list_push(menu_driver_data,
               menu_userdata, disp_list->info, disp_list->type) == 0)
         return true;
   return false;
}