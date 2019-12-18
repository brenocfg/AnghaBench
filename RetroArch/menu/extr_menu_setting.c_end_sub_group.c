#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rarch_setting_t ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ rarch_setting_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ST_END_SUB_GROUP ; 
 int /*<<< orphan*/  setting_group_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void end_sub_group(
      rarch_setting_t **list,
      rarch_setting_info_t *list_info,
      const char *parent_group)
{
   (*list)[list_info->index++] = setting_group_setting (ST_END_SUB_GROUP, 0, parent_group);
}