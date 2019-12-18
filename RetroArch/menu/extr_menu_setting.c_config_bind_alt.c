#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct retro_keybind {int dummy; } ;
typedef  int /*<<< orphan*/  rarch_setting_t ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ rarch_setting_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ rarch_setting_group_info_t ;

/* Variables and functions */
 int SD_FREE_FLAG_NAME ; 
 int SD_FREE_FLAG_SHORT ; 
 int /*<<< orphan*/  SETTINGS_DATA_LIST_CURRENT_ADD_FREE_FLAGS (int /*<<< orphan*/ **,TYPE_1__*,int) ; 
 int /*<<< orphan*/  setting_bind_setting (char const*,char const*,struct retro_keybind*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct retro_keybind const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void config_bind_alt(
      rarch_setting_t **list,
      rarch_setting_info_t *list_info,
      struct retro_keybind *target,
      uint32_t player, uint32_t player_offset,
      const char *name, const char *SHORT,
      const struct retro_keybind *default_value,
      rarch_setting_group_info_t *group_info,
      rarch_setting_group_info_t *subgroup_info,
      const char *parent_group)
{
   (*list)[list_info->index++] = setting_bind_setting(name, SHORT, target,
         player, player_offset, default_value,
         group_info->name, subgroup_info->name, parent_group,
         true);
   /* Request name and short description to be freed later */
   SETTINGS_DATA_LIST_CURRENT_ADD_FREE_FLAGS(list, list_info, SD_FREE_FLAG_NAME | SD_FREE_FLAG_SHORT);
}