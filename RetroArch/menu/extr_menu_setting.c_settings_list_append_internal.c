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
struct TYPE_3__ {int size; } ;
typedef  TYPE_1__ rarch_setting_info_t ;

/* Variables and functions */
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool settings_list_append_internal(
      rarch_setting_t **list,
      rarch_setting_info_t *list_info)
{
   unsigned new_size              = list_info->size * 2;
   rarch_setting_t *list_settings = (rarch_setting_t*)
      realloc(*list, sizeof(rarch_setting_t) * new_size);

   if (!list_settings)
      return false;
   list_info->size                = new_size;
   *list                          = list_settings;

   return true;
}