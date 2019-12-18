#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* path; int /*<<< orphan*/  display_name; } ;
typedef  TYPE_1__ core_info_t ;
struct TYPE_5__ {size_t count; TYPE_1__* list; } ;
typedef  TYPE_2__ core_info_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  path_basename (char const*) ; 
 int /*<<< orphan*/  string_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

bool core_info_list_get_display_name(core_info_list_t *core_info_list,
      const char *path, char *s, size_t len)
{
   size_t i;

   if (!core_info_list)
      return false;

   for (i = 0; i < core_info_list->count; i++)
   {
      const core_info_t *info = &core_info_list->list[i];

      if (!string_is_equal(path_basename(info->path), path_basename(path)))
         continue;

      if (!info->display_name)
         continue;

      strlcpy(s, info->display_name, len);
      return true;
   }

   return false;
}