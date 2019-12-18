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
struct TYPE_7__ {char const* path; } ;
typedef  TYPE_1__ core_info_t ;
struct TYPE_8__ {size_t count; } ;
typedef  TYPE_2__ core_info_list_t ;

/* Variables and functions */
 TYPE_1__* core_info_get (TYPE_2__*,size_t) ; 
 char* path_basename (char const*) ; 
 scalar_t__ string_is_equal (char*,char const*) ; 

__attribute__((used)) static core_info_t *core_info_find_internal(
      core_info_list_t *list,
      const char *core)
{
   size_t i;
   const char *core_path_basename = path_basename(core);

   for (i = 0; i < list->count; i++)
   {
      core_info_t *info = core_info_get(list, i);

      if (!info || !info->path)
         continue;
      if (string_is_equal(path_basename(info->path), core_path_basename))
         return info;
   }

   return NULL;
}