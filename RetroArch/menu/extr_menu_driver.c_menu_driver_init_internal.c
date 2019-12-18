#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  menu_driver; } ;
struct TYPE_10__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_11__ {TYPE_7__* driver_ctx; int /*<<< orphan*/  userdata; } ;
typedef  TYPE_3__ menu_handle_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* lists_init ) (TYPE_3__*) ;int /*<<< orphan*/  ident; scalar_t__ (* init ) (int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 
 TYPE_7__* menu_driver_ctx ; 
 TYPE_3__* menu_driver_data ; 
 int /*<<< orphan*/  menu_init (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_userdata ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static bool menu_driver_init_internal(bool video_is_threaded)
{
   if (menu_driver_ctx->init)
   {
      menu_driver_data               = (menu_handle_t*)
         menu_driver_ctx->init(&menu_userdata, video_is_threaded);
      menu_driver_data->userdata     = menu_userdata;
      menu_driver_data->driver_ctx   = menu_driver_ctx;
   }

   if (!menu_driver_data || !menu_init(menu_driver_data))
      return false;

   {
      settings_t *settings           = config_get_ptr();
      strlcpy(settings->arrays.menu_driver, menu_driver_ctx->ident,
            sizeof(settings->arrays.menu_driver));
   }

   if (menu_driver_ctx->lists_init)
      if (!menu_driver_ctx->lists_init(menu_driver_data))
         return false;

   return true;
}