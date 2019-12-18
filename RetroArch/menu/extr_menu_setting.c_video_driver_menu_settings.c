#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rarch_setting_t ;
typedef  int /*<<< orphan*/  rarch_setting_info_t ;
typedef  int /*<<< orphan*/  rarch_setting_group_info_t ;
struct TYPE_5__ {int /*<<< orphan*/  flicker_filter_index; int /*<<< orphan*/  gamma_correction; int /*<<< orphan*/  pal60_enable; } ;
struct TYPE_6__ {TYPE_1__ screen; int /*<<< orphan*/  softfilter_enable; } ;
struct TYPE_7__ {TYPE_2__ console; } ;
typedef  TYPE_3__ global_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_VIDEO_APPLY_STATE_CHANGES ; 
 int /*<<< orphan*/  CONFIG_BOOL (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_UINT (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_GAMMA_SETTING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PAL60_ENABLE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_OFF ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ON ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PAL60_ENABLE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_VIDEO_FILTER_FLICKER ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_VIDEO_GAMMA ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_VIDEO_SOFT_FILTER ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VIDEO_FILTER_FLICKER ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VIDEO_GAMMA ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VIDEO_SOFT_FILTER ; 
 int SD_FLAG_ADVANCED ; 
 int SD_FLAG_CMD_APPLY_AUTO ; 
 int /*<<< orphan*/  SD_FLAG_NONE ; 
 int /*<<< orphan*/  SETTINGS_DATA_LIST_CURRENT_ADD_FLAGS (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  general_read_handler ; 
 int /*<<< orphan*/  general_write_handler ; 
 TYPE_3__* global_get_ptr () ; 
 int /*<<< orphan*/  menu_settings_list_current_add_cmd (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_settings_list_current_add_range (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 

void video_driver_menu_settings(void **list_data, void *list_info_data,
      void *group_data, void *subgroup_data, const char *parent_group)
{
#ifdef HAVE_MENU
   rarch_setting_t **list                    = (rarch_setting_t**)list_data;
   rarch_setting_info_t *list_info           = (rarch_setting_info_t*)list_info_data;
   rarch_setting_group_info_t *group_info    = (rarch_setting_group_info_t*)group_data;
   rarch_setting_group_info_t *subgroup_info = (rarch_setting_group_info_t*)subgroup_data;
   global_t                        *global   = global_get_ptr();

   (void)list;
   (void)list_info;
   (void)group_info;
   (void)subgroup_info;
   (void)global;

#if defined(__CELLOS_LV2__)
   CONFIG_BOOL(
         list, list_info,
         &global->console.screen.pal60_enable,
         MENU_ENUM_LABEL_PAL60_ENABLE,
         MENU_ENUM_LABEL_VALUE_PAL60_ENABLE,
         false,
         MENU_ENUM_LABEL_VALUE_OFF,
         MENU_ENUM_LABEL_VALUE_ON,
         group_info,
         subgroup_info,
         parent_group,
         general_write_handler,
         general_read_handler,
         SD_FLAG_NONE);
#endif
#if defined(GEKKO) || defined(_XBOX360)
   CONFIG_UINT(
         list, list_info,
         &global->console.screen.gamma_correction,
         MENU_ENUM_LABEL_VIDEO_GAMMA,
         MENU_ENUM_LABEL_VALUE_VIDEO_GAMMA,
         0,
         group_info,
         subgroup_info,
         parent_group,
         general_write_handler,
         general_read_handler);
   menu_settings_list_current_add_cmd(
         list,
         list_info,
         CMD_EVENT_VIDEO_APPLY_STATE_CHANGES);
   menu_settings_list_current_add_range(
         list,
         list_info,
         0,
         MAX_GAMMA_SETTING,
         1,
         true,
         true);
   SETTINGS_DATA_LIST_CURRENT_ADD_FLAGS(list, list_info,
         SD_FLAG_CMD_APPLY_AUTO|SD_FLAG_ADVANCED);
#endif
#if defined(_XBOX1) || defined(HW_RVL)
   CONFIG_BOOL(
         list, list_info,
         &global->console.softfilter_enable,
         MENU_ENUM_LABEL_VIDEO_SOFT_FILTER,
         MENU_ENUM_LABEL_VALUE_VIDEO_SOFT_FILTER,
         false,
         MENU_ENUM_LABEL_VALUE_OFF,
         MENU_ENUM_LABEL_VALUE_ON,
         group_info,
         subgroup_info,
         parent_group,
         general_write_handler,
         general_read_handler,
         SD_FLAG_NONE);
   menu_settings_list_current_add_cmd(
         list,
         list_info,
         CMD_EVENT_VIDEO_APPLY_STATE_CHANGES);
#endif
#ifdef _XBOX1
   CONFIG_UINT(
         list, list_info,
         &global->console.screen.flicker_filter_index,
         MENU_ENUM_LABEL_VIDEO_FILTER_FLICKER,
         MENU_ENUM_LABEL_VALUE_VIDEO_FILTER_FLICKER,
         0,
         group_info,
         subgroup_info,
         parent_group,
         general_write_handler,
         general_read_handler);
   menu_settings_list_current_add_range(list, list_info,
         0, 5, 1, true, true);
#endif
#endif
}