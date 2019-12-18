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
struct TYPE_6__ {char const* path; } ;
typedef  TYPE_1__ core_info_t ;
struct TYPE_7__ {size_t count; TYPE_1__* list; } ;
typedef  TYPE_2__ core_info_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  path_basename (char const*) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool core_info_list_get_info(core_info_list_t *core_info_list,
      core_info_t *out_info, const char *path)
{
   size_t i;
   if (!core_info_list || !out_info)
      return false;

   memset(out_info, 0, sizeof(*out_info));

   for (i = 0; i < core_info_list->count; i++)
   {
      const core_info_t *info = &core_info_list->list[i];

      if (string_is_equal(path_basename(info->path),
               path_basename(path)))
      {
         *out_info = *info;
         return true;
      }
   }

   return false;
}