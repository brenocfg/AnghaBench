#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {int /*<<< orphan*/  i; } ;
typedef  int uint32_t ;
struct string_list {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  path_content_history; int /*<<< orphan*/  directory_playlist; } ;
struct TYPE_14__ {TYPE_1__ paths; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_15__ {char* content_crc; char* content_path; char* hostname; char* core_name; char* subsystem_name; int found; char* core_path; char* core_extensions; int /*<<< orphan*/  title; int /*<<< orphan*/  callback; int /*<<< orphan*/  handler; struct TYPE_15__* state; int /*<<< orphan*/  type; struct string_list* lpl_list; } ;
typedef  TYPE_4__ retro_task_t ;
typedef  TYPE_4__ netplay_crc_handle_t ;
struct TYPE_16__ {unsigned int count; TYPE_2__* list; } ;
typedef  TYPE_6__ core_info_list_t ;
struct TYPE_13__ {char* core_name; char const* path; char const* supported_extensions; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_TYPE_BLOCKING ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  core_info_get_list (TYPE_6__**) ; 
 struct string_list* dir_list_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  netplay_crc_scan_callback ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 scalar_t__ string_is_not_equal (char*,char*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ,union string_list_elem_attr) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 TYPE_4__* task_init () ; 
 int /*<<< orphan*/  task_netplay_crc_scan_handler ; 
 int /*<<< orphan*/  task_queue_push (TYPE_4__*) ; 

bool task_push_netplay_crc_scan(uint32_t crc, char* name,
      const char *hostname, const char *core_name, const char *subsystem)
{
   unsigned i;
   union string_list_elem_attr attr;
   struct string_list *lpl_list = NULL;
   core_info_list_t *info       = NULL;
   settings_t        *settings  = config_get_ptr();
   retro_task_t          *task  = task_init();
   netplay_crc_handle_t *state  = (netplay_crc_handle_t*)
      calloc(1, sizeof(*state));

   if (!task || !state)
      goto error;

   state->content_crc[0]    = '\0';
   state->content_path[0]   = '\0';
   state->hostname[0]       = '\0';
   state->core_name[0]      = '\0';
   state->subsystem_name[0] = '\0';
   attr.i = 0;

   snprintf(state->content_crc,
         sizeof(state->content_crc),
         "%08X|crc", crc);

   strlcpy(state->content_path,
         name, sizeof(state->content_path));
   strlcpy(state->hostname,
         hostname, sizeof(state->hostname));
   strlcpy(state->subsystem_name,
         subsystem, sizeof(state->subsystem_name));
   strlcpy(state->core_name,
         core_name, sizeof(state->core_name));

   lpl_list = dir_list_new(settings->paths.directory_playlist,
         NULL, true, true, true, false);

   if (!lpl_list)
      goto error;

   state->lpl_list = lpl_list;

   string_list_append(state->lpl_list,
         settings->paths.path_content_history, attr);
   state->found = false;

   core_info_get_list(&info);

   for (i = 0; i < info->count; i++)
   {
      /* check if the core name matches.
         TO-DO :we could try to load the core too to check
         if the version string matches too */
#if 0
      printf("Info: %s State: %s", info->list[i].core_name, state->core_name);
#endif
      if (string_is_equal(info->list[i].core_name, state->core_name))
      {
         strlcpy(state->core_path,
               info->list[i].path, sizeof(state->core_path));

         if (string_is_not_equal(state->content_path, "N/A") &&
            !string_is_empty(info->list[i].supported_extensions))
         {
            strlcpy(state->core_extensions,
                  info->list[i].supported_extensions,
                  sizeof(state->core_extensions));
         }
         break;
      }
   }

   /* blocking means no other task can run while this one is running,
    * which is the default */
   task->type           = TASK_TYPE_BLOCKING;
   task->state          = state;
   task->handler        = task_netplay_crc_scan_handler;
   task->callback       = netplay_crc_scan_callback;
   task->title          = strdup("Looking for matching content...");

   task_queue_push(task);

   return true;

error:
   if (state)
      free(state);
   if (task)
      free(task);

   return false;
}