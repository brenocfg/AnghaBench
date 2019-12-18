#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int flags; int (* action_right ) (TYPE_1__*,int) ;int /*<<< orphan*/  action_select; int /*<<< orphan*/  action_left; int /*<<< orphan*/  change_handler; } ;
typedef  TYPE_1__ rarch_setting_t ;
typedef  enum menu_setting_ctl_state { ____Placeholder_menu_setting_ctl_state } menu_setting_ctl_state ;

/* Variables and functions */
#define  MENU_SETTING_CTL_ACTION_RIGHT 131 
#define  MENU_SETTING_CTL_IS_OF_PATH_TYPE 130 
#define  MENU_SETTING_CTL_NEW 129 
#define  MENU_SETTING_CTL_NONE 128 
 int /*<<< orphan*/  RARCH_MENU_CTL_UPDATE_SAVESTATE_THUMBNAIL_IMAGE ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_UPDATE_SAVESTATE_THUMBNAIL_PATH ; 
 int SD_FLAG_BROWSER_ACTION ; 
 int /*<<< orphan*/  ST_ACTION ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* menu_setting_new () ; 
 int /*<<< orphan*/  setting_get_type (TYPE_1__*) ; 
 int stub1 (TYPE_1__*,int) ; 

bool menu_setting_ctl(enum menu_setting_ctl_state state, void *data)
{
   uint64_t flags;

   switch (state)
   {
      case MENU_SETTING_CTL_IS_OF_PATH_TYPE:
         {
            bool cbs_bound           = false;
            rarch_setting_t *setting = (rarch_setting_t*)data;

            if (!setting)
               return false;

            flags                    = setting->flags;

            if (setting_get_type(setting) != ST_ACTION)
               return false;

            if (!setting->change_handler)
               return false;

            cbs_bound = (setting->action_right != NULL);
            cbs_bound = cbs_bound || setting->action_left;
            cbs_bound = cbs_bound || setting->action_select;

            if (!cbs_bound)
               return false;

            if (!(flags & SD_FLAG_BROWSER_ACTION))
               return false;
         }
         break;
      case MENU_SETTING_CTL_NEW:
         {
            rarch_setting_t **setting = (rarch_setting_t**)data;
            if (!setting)
               return false;
            *setting = menu_setting_new();
         }
         break;
      case MENU_SETTING_CTL_ACTION_RIGHT:
         {
            rarch_setting_t *setting = (rarch_setting_t*)data;
            if (!setting)
               return false;

            if (setting->action_right)
            {
               int ret = setting->action_right(setting, false);
               menu_driver_ctl(
                     RARCH_MENU_CTL_UPDATE_SAVESTATE_THUMBNAIL_PATH, NULL);
               menu_driver_ctl(
                     RARCH_MENU_CTL_UPDATE_SAVESTATE_THUMBNAIL_IMAGE, NULL);
               if (ret == -1)
                  return false;
            }
            else
               return false;
         }
         break;
      case MENU_SETTING_CTL_NONE:
      default:
         break;
   }

   return true;
}