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
struct TYPE_5__ {size_t firmware_count; TYPE_1__* firmware; } ;
typedef  TYPE_2__ core_info_t ;
typedef  int /*<<< orphan*/  core_info_list_t ;
struct TYPE_4__ {int missing; int /*<<< orphan*/  path; int /*<<< orphan*/  optional; } ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_WARN (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* core_info_find_internal (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  path_is_valid (char*) ; 
 scalar_t__ string_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool core_info_list_update_missing_firmware_internal(
      core_info_list_t *core_info_list,
      const char *core,
      const char *systemdir,
      bool *set_missing_bios)
{
   size_t i;
   core_info_t      *info = NULL;
   char             *path = NULL;
   size_t       path_size = PATH_MAX_LENGTH * sizeof(char);

   if (!core_info_list || !core)
      return false;

   info                   = core_info_find_internal(core_info_list, core);

   if (!info)
      return false;

   path                   = (char*)malloc(path_size);

   if (!path)
      return false;

   path[0]                = '\0';

   for (i = 0; i < info->firmware_count; i++)
   {
      if (string_is_empty(info->firmware[i].path))
         continue;

      fill_pathname_join(path, systemdir,
            info->firmware[i].path, path_size);
      info->firmware[i].missing = !path_is_valid(path);
      if (info->firmware[i].missing && !info->firmware[i].optional)
      {
         *set_missing_bios = true;
         RARCH_WARN("Firmware missing: %s\n", info->firmware[i].path);
      }
   }

   free(path);
   return true;
}