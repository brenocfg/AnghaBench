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
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ rarch_setting_group_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  setting_action_setting (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void config_action_alt(
      rarch_setting_t **list,
      rarch_setting_info_t *list_info,
      const char *name, const char *SHORT,
      rarch_setting_group_info_t *group_info,
      rarch_setting_group_info_t *subgroup_info,
      const char *parent_group)
{
   (*list)[list_info->index++] = setting_action_setting(name, SHORT,
         group_info->name, subgroup_info->name, parent_group,
         true);
}