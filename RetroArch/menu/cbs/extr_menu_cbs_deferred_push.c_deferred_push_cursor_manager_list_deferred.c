#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path_content_database; } ;
struct TYPE_8__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  rdb_path ;
struct TYPE_9__ {char* path; char* path_b; char* path_c; } ;
typedef  TYPE_3__ menu_displaylist_info_t ;
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLIST_DATABASE_QUERY ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_file_new_from_path_to_string (char const*) ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  config_get_string (int /*<<< orphan*/ *,char*,char**) ; 
 int deferred_push_dlist (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 

__attribute__((used)) static int deferred_push_cursor_manager_list_deferred(
      menu_displaylist_info_t *info)
{
   char rdb_path[PATH_MAX_LENGTH];
   int ret                        = -1;
   char *query                    = NULL;
   char *rdb                      = NULL;
   const char *path               = info->path;
   config_file_t *conf            = NULL;
   
   if (!(conf = config_file_new_from_path_to_string(path)))
      return -1;

   if (!config_get_string(conf, "query", &query))
      goto end;

   if (!config_get_string(conf, "rdb", &rdb))
      goto end;

   rdb_path[0] = '\0';

   {
      settings_t *settings           = config_get_ptr();
      if (settings)
         fill_pathname_join(rdb_path,
               settings->paths.path_content_database,
               rdb, sizeof(rdb_path));
   }

   if (!string_is_empty(info->path_b))
      free(info->path_b);

   if (!string_is_empty(info->path_c))
      free(info->path_c);

   info->path_b    = strdup(info->path);

   if (!string_is_empty(info->path))
      free(info->path);

   info->path_c    = strdup(query);
   info->path      = strdup(rdb_path);

   ret             = deferred_push_dlist(info, DISPLAYLIST_DATABASE_QUERY);

end:
   config_file_free(conf);
   free(rdb);
   free(query);
   return ret;
}