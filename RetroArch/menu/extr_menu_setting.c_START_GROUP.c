#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rarch_setting_t ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ rarch_setting_info_t ;
struct TYPE_7__ {char const* name; } ;
typedef  TYPE_2__ rarch_setting_group_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ST_GROUP ; 
 int /*<<< orphan*/  setting_group_setting (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  settings_list_append (int /*<<< orphan*/ **,TYPE_1__*) ; 

__attribute__((used)) static void START_GROUP(rarch_setting_t **list, rarch_setting_info_t *list_info,
      rarch_setting_group_info_t *group_info,
      const char *name, const char *parent_group)
{
   group_info->name = name;
   if (!settings_list_append(list, list_info))
      return;
   (*list)[list_info->index++] = setting_group_setting (ST_GROUP, name, parent_group);
}