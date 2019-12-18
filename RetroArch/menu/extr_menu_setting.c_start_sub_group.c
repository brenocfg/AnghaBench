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
typedef  int /*<<< orphan*/  rarch_setting_t ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ rarch_setting_info_t ;
struct TYPE_8__ {char const* name; } ;
typedef  TYPE_2__ rarch_setting_group_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ST_SUB_GROUP ; 
 int /*<<< orphan*/  setting_subgroup_setting (int /*<<< orphan*/ ,char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  settings_list_append (int /*<<< orphan*/ **,TYPE_1__*) ; 

__attribute__((used)) static bool start_sub_group(rarch_setting_t **list,
      rarch_setting_info_t *list_info, const char *name,
      rarch_setting_group_info_t *group_info,
      rarch_setting_group_info_t *subgroup_info,
      const char *parent_group)
{
   subgroup_info->name = name;

   if (!settings_list_append(list, list_info))
      return false;
   (*list)[list_info->index++] = setting_subgroup_setting (ST_SUB_GROUP,
         name, group_info->name, parent_group, false);
   return true;
}