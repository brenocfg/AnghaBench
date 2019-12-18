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
struct TYPE_4__ {int /*<<< orphan*/  action; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ menu_ctx_list_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* list_cache ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_userdata ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool menu_driver_list_cache(menu_ctx_list_t *list)
{
   if (!list || !menu_driver_ctx || !menu_driver_ctx->list_cache)
      return false;

   menu_driver_ctx->list_cache(menu_userdata,
         list->type, list->action);
   return true;
}