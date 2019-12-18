#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  databases_list; int /*<<< orphan*/  supported_extensions_list; } ;
typedef  TYPE_1__ core_info_t ;
struct TYPE_4__ {size_t count; TYPE_1__* list; } ;

/* Variables and functions */
 TYPE_2__* core_info_curr_list ; 
 int /*<<< orphan*/  free (char*) ; 
 char* path_basename (char const*) ; 
 char* path_get_extension (char const*) ; 
 int /*<<< orphan*/  path_remove_extension (char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_list_find_elem (int /*<<< orphan*/ ,char*) ; 

bool core_info_database_supports_content_path(
      const char *database_path, const char *path)
{
   char *database           = NULL;
   const char *new_path     = path_basename(database_path);

   if (string_is_empty(new_path))
      return false;

   database                 = strdup(new_path);

   if (string_is_empty(database))
      goto error;

   path_remove_extension(database);

   if (core_info_curr_list)
   {
      size_t i;

      for (i = 0; i < core_info_curr_list->count; i++)
      {
         const core_info_t *info = &core_info_curr_list->list[i];

         if (!string_list_find_elem(info->supported_extensions_list,
                  path_get_extension(path)))
            continue;

         if (!string_list_find_elem(info->databases_list, database))
            continue;

         free(database);
         return true;
      }
   }

error:
   if (database)
      free(database);
   return false;
}