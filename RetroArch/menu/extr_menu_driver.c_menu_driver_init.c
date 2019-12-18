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
struct TYPE_2__ {int /*<<< orphan*/  (* context_reset ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_CORE_INFO_INIT ; 
 int /*<<< orphan*/  CMD_EVENT_LOAD_CORE_PERSIST ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* menu_driver_ctx ; 
 scalar_t__ menu_driver_data ; 
 scalar_t__ menu_driver_init_internal (int) ; 
 int /*<<< orphan*/  menu_userdata ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

bool menu_driver_init(bool video_is_threaded)
{
   command_event(CMD_EVENT_CORE_INFO_INIT, NULL);
   command_event(CMD_EVENT_LOAD_CORE_PERSIST, NULL);

   if (  menu_driver_data || 
         menu_driver_init_internal(video_is_threaded))
   {
      if (menu_driver_ctx && menu_driver_ctx->context_reset)
      {
         menu_driver_ctx->context_reset(menu_userdata, video_is_threaded);
         return true;
      }
   }

   return false;
}