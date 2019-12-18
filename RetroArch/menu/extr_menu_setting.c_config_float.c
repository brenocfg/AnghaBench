#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  ui_type; } ;
typedef  TYPE_1__ rarch_setting_t ;
struct TYPE_14__ {int index; } ;
typedef  TYPE_2__ rarch_setting_info_t ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ rarch_setting_group_info_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
typedef  int /*<<< orphan*/  change_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_SETTINGS_LIST_CURRENT_ADD_ENUM_IDX_PTR (TYPE_1__**,TYPE_2__*,int) ; 
 int /*<<< orphan*/  MENU_SETTINGS_LIST_CURRENT_ADD_ENUM_VALUE_IDX (TYPE_1__**,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ST_UI_TYPE_FLOAT_SPINBOX ; 
 int /*<<< orphan*/  msg_hash_to_str (int) ; 
 TYPE_1__ setting_float_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,float,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void config_float(
      rarch_setting_t **list,
      rarch_setting_info_t *list_info,
      float *target,
      enum msg_hash_enums name_enum_idx,
      enum msg_hash_enums SHORT_enum_idx,
      float default_value, const char *rounding,
      rarch_setting_group_info_t *group_info,
      rarch_setting_group_info_t *subgroup_info,
      const char *parent_group,
      change_handler_t change_handler, change_handler_t read_handler)
{
   (*list)[list_info->index++]             = setting_float_setting(
         msg_hash_to_str(name_enum_idx),
         msg_hash_to_str(SHORT_enum_idx), target, default_value, rounding,
         group_info->name, subgroup_info->name, parent_group,
         change_handler, read_handler, false);
   (*list)[list_info->index - 1].ui_type   = ST_UI_TYPE_FLOAT_SPINBOX;

   MENU_SETTINGS_LIST_CURRENT_ADD_ENUM_IDX_PTR(list, list_info, name_enum_idx);
   MENU_SETTINGS_LIST_CURRENT_ADD_ENUM_VALUE_IDX(list, list_info, SHORT_enum_idx);
}