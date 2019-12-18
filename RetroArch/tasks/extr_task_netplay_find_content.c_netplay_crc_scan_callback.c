#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct string_list {unsigned int size; TYPE_1__* elems; } ;
struct retro_system_info {char* library_name; } ;
typedef  int /*<<< orphan*/  retro_task_t ;
struct TYPE_10__ {char* subsystem_name; char* content_path; char* core_path; char* core_name; int /*<<< orphan*/ * hostname; scalar_t__ current; scalar_t__ contentless; } ;
typedef  TYPE_2__ netplay_crc_handle_t ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ content_ctx_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NETPLAY_INIT_DIRECT ; 
 int /*<<< orphan*/  CMD_EVENT_NETPLAY_INIT_DIRECT_DEFERRED ; 
 int /*<<< orphan*/  CMD_EVENT_RESUME ; 
 int /*<<< orphan*/  CORE_TYPE_PLAIN ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NETPLAY_LOAD_CONTENT_MANUALLY ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  content_add_subsystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  content_clear_subsystem () ; 
 int /*<<< orphan*/  content_set_subsystem_by_name (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 struct retro_system_info* runloop_get_libretro_system_info () ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char*,char*) ; 
 int /*<<< orphan*/  task_push_load_content_with_core_from_menu (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_push_load_new_core (char*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_push_load_subsystem_with_core_from_menu (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_push_start_current_core (TYPE_3__*) ; 

__attribute__((used)) static void netplay_crc_scan_callback(retro_task_t *task,
      void *task_data,
      void *user_data, const char *error)
{
   netplay_crc_handle_t *state     = (netplay_crc_handle_t*)task_data;
   content_ctx_info_t content_info = {0};

   if (!state)
      return;

   fflush(stdout);

   if (!string_is_empty(state->subsystem_name) && !string_is_equal(state->subsystem_name, "N/A"))
   {
      content_ctx_info_t content_info  = {0};
      struct string_list *game_list = string_split(state->content_path, "|");
      unsigned i = 0;

      task_push_load_new_core(state->core_path, NULL,
            &content_info, CORE_TYPE_PLAIN, NULL, NULL);
      content_clear_subsystem();
      if (!content_set_subsystem_by_name(state->subsystem_name))
         RARCH_LOG("[Lobby] Subsystem not found in implementation\n");

      for (i = 0; i < game_list->size; i++)
         content_add_subsystem(game_list->elems[i].data);
      task_push_load_subsystem_with_core_from_menu(
         NULL, &content_info,
         CORE_TYPE_PLAIN, NULL, NULL);
      string_list_free(game_list);
      return;
   }

   /* regular core with content file */
   if (!string_is_empty(state->core_path) && !string_is_empty(state->content_path)
      && !state->contentless && !state->current)
   {
      struct retro_system_info *system = runloop_get_libretro_system_info();

      RARCH_LOG("[Lobby] Loading core %s with content file %s\n",
         state->core_path, state->content_path);

      command_event(CMD_EVENT_NETPLAY_INIT_DIRECT_DEFERRED, state->hostname);

      if (system && string_is_equal(system->library_name, state->core_name))
         task_push_load_content_with_core_from_menu(
               state->content_path, &content_info,
               CORE_TYPE_PLAIN, NULL, NULL);
      else
      {
         task_push_load_new_core(state->core_path, NULL,
               &content_info, CORE_TYPE_PLAIN, NULL, NULL);
         task_push_load_content_with_core_from_menu(
               state->content_path, &content_info,
               CORE_TYPE_PLAIN, NULL, NULL);
      }

   }
   else

   /* contentless core */
   if (!string_is_empty(state->core_path) && !string_is_empty(state->content_path)
      && state->contentless)
   {
      content_ctx_info_t content_info  = {0};
      struct retro_system_info *system = runloop_get_libretro_system_info();

      RARCH_LOG("[Lobby] Loading contentless core %s\n", state->core_path);

      command_event(CMD_EVENT_NETPLAY_INIT_DIRECT_DEFERRED, state->hostname);

      if (!string_is_equal(system->library_name, state->core_name))
         task_push_load_new_core(state->core_path, NULL,
               &content_info, CORE_TYPE_PLAIN, NULL, NULL);

      task_push_start_current_core(&content_info);
   }
   /* regular core with current content */
   else if (!string_is_empty(state->core_path) && !string_is_empty(state->content_path)
      && state->current)
   {
      RARCH_LOG("[Lobby] Loading core %s with current content\n", state->core_path);
      command_event(CMD_EVENT_NETPLAY_INIT_DIRECT, state->hostname);
      command_event(CMD_EVENT_RESUME, NULL);
   }
   /* no match found */
   else
   {
      RARCH_LOG("[Lobby] Couldn't find a suitable %s\n",
         string_is_empty(state->content_path) ? "content file" : "core");
      runloop_msg_queue_push(
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NETPLAY_LOAD_CONTENT_MANUALLY),
            1, 480, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   }

   free(state);
}