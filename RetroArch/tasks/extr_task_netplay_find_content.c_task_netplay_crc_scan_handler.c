#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct string_list {size_t size; TYPE_1__* elems; } ;
struct playlist_entry {char* path; char* crc32; } ;
struct TYPE_13__ {scalar_t__ state; } ;
typedef  TYPE_2__ retro_task_t ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_14__ {int found; int contentless; char* content_crc; char* content_path; int current; char* subsystem_name; char const* core_extensions; int /*<<< orphan*/  hostname; struct string_list* lpl_list; } ;
typedef  TYPE_3__ netplay_crc_handle_t ;
typedef  int /*<<< orphan*/  entry ;
typedef  int /*<<< orphan*/  current ;
struct TYPE_12__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NETPLAY_INIT_DIRECT_DEFERRED ; 
 int /*<<< orphan*/  COLLECTION_SIZE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NETPLAY_COMPAT_CONTENT_FOUND ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  begin_task (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int content_get_crc () ; 
 scalar_t__ core_requires_content (TYPE_3__*) ; 
 int /*<<< orphan*/  finish_task (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  get_entry (char*,int,char const*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_get_extension (char const*) ; 
 int /*<<< orphan*/  playlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,size_t,struct playlist_entry const**) ; 
 unsigned int playlist_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * playlist_init (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strstr (char const*,char*) ; 
 int /*<<< orphan*/  task_set_data (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  task_set_progress (TYPE_2__*,int) ; 

__attribute__((used)) static void task_netplay_crc_scan_handler(retro_task_t *task)
{
   size_t i, j, k;
   char entry[PATH_MAX_LENGTH];
   bool have_crc               = false;
   netplay_crc_handle_t *state = (netplay_crc_handle_t*)task->state;

   begin_task(task, "Looking for compatible content...");

   /* start by checking cases that don't require a search */

   /* the core doesn't have any content to match, so fast-succeed */
   if (!core_requires_content(state))
   {
      state->found = true;
      state->contentless = true;
      task_set_data(task, state);
      finish_task(task, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NETPLAY_COMPAT_CONTENT_FOUND));
      return;
   }

   /* if this list is null, it means that RA failed to open the playlist directory */
   if (!state->lpl_list)
   {
      finish_task(task, "Playlist directory not found");
      free(state);
      return;
   }

   /* We opened the playlist directory, but there's nothing there. Nothing to do. */
   if (state->lpl_list->size == 0 && core_requires_content(state))
   {
      string_list_free(state->lpl_list);
      finish_task(task, "There are no playlists available; cannot execute search");
      command_event(CMD_EVENT_NETPLAY_INIT_DIRECT_DEFERRED, state->hostname);
      free(state);
      return;
   }

   have_crc = !string_is_equal(state->content_crc, "00000000|crc");

   /* if content is already loaded and the lobby gave us a CRC, check the loaded content first */
   if (have_crc && content_get_crc() > 0)
   {
      char current[PATH_MAX_LENGTH];

      RARCH_LOG("[Lobby] Testing CRC matching for: %s\n", state->content_crc);

      snprintf(current, sizeof(current), "%X|crc", content_get_crc());
      RARCH_LOG("[Lobby] Current content crc: %s\n", current);

      if (string_is_equal(current, state->content_crc))
      {
         RARCH_LOG("[Lobby] CRC match %s with currently loaded content\n", current);
         strlcpy(state->content_path, "N/A", sizeof(state->content_path));
         state->found = true;
         state->current = true;
         task_set_data(task, state);
         finish_task(task, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NETPLAY_COMPAT_CONTENT_FOUND));
         string_list_free(state->lpl_list);
         return;
      }
   }

   /* now let's do the search */
   if (string_is_empty(state->subsystem_name) || string_is_equal(state->subsystem_name, "N/A"))
   {
      for (i = 0; i < state->lpl_list->size; i++)
      {
         playlist_t *playlist   = NULL;
         unsigned playlist_size = 0;
         const char *lpl_path   = state->lpl_list->elems[i].data;

         /* skip files without .lpl file extension */
         if (!strstr(lpl_path, ".lpl"))
            continue;

         RARCH_LOG("[Lobby] Searching playlist: %s\n", lpl_path);
         playlist      = playlist_init(lpl_path, COLLECTION_SIZE);
         playlist_size = playlist_get_size(playlist);

         for (j = 0; j < playlist_size; j++)
         {
            const char *playlist_path     = NULL;
            const char *playlist_crc32    = NULL;
            const struct playlist_entry *playlist_entry = NULL;

            playlist_get_index(playlist, j, &playlist_entry);

            playlist_path = playlist_entry->path;
            playlist_crc32 = playlist_entry->crc32;

            if (have_crc && string_is_equal(playlist_crc32, state->content_crc))
            {
               RARCH_LOG("[Lobby] CRC match %s\n", playlist_crc32);
               strlcpy(state->content_path, playlist_path, sizeof(state->content_path));
               state->found = true;
               task_set_data(task, state);
               finish_task(task, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NETPLAY_COMPAT_CONTENT_FOUND));
               string_list_free(state->lpl_list);
               playlist_free(playlist);
               return;
            }

            get_entry(entry, sizeof(entry), playlist_path);

            /* See if the filename is a match. The response depends on whether or not we are doing a CRC
            * search.
            * Otherwise, on match we complete the task and mark it as successful immediately.
            */

            if (!string_is_empty(entry) &&
               string_is_equal(entry, state->content_path) &&
               strstr(state->core_extensions, path_get_extension(playlist_path)))
            {
               RARCH_LOG("[Lobby] Filename match %s\n", playlist_path);

               strlcpy(state->content_path, playlist_path, sizeof(state->content_path));
               state->found = true;
               task_set_data(task, state);
               finish_task(task, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NETPLAY_COMPAT_CONTENT_FOUND));
               string_list_free(state->lpl_list);
               playlist_free(playlist);
               return;
            }

            task_set_progress(task, (int)(j / playlist_size * 100.0));
         }

         playlist_free(playlist);
      }
   }
   else
   {
      bool found[100];
      struct string_list *game_list = string_split(state->content_path, "|");

      for (i = 0; i < game_list->size; i++)
      {
         found[i] = false;

         for (j = 0; j < state->lpl_list->size && !found[i]; j++)
         {
            playlist_t *playlist   = NULL;
            unsigned playlist_size = 0;
            const char *lpl_path   = state->lpl_list->elems[j].data;

            /* skip files without .lpl file extension */
            if (!strstr(lpl_path, ".lpl"))
               continue;

            RARCH_LOG("[Lobby] Searching content %d/%d (%s) in playlist: %s\n", i + 1, game_list->size, game_list->elems[i].data, lpl_path);
            playlist      = playlist_init(lpl_path, COLLECTION_SIZE);
            playlist_size = playlist_get_size(playlist);

            for (k = 0; k < playlist_size && !found[i]; k++)
            {
               const struct playlist_entry *playlist_entry = NULL;

               playlist_get_index(playlist, k, &playlist_entry);

               get_entry(entry, sizeof(entry), playlist_entry->path);

               if (!string_is_empty(entry) &&
                  strstr(game_list->elems[i].data, entry) &&
                  strstr(state->core_extensions, path_get_extension(playlist_entry->path)))
               {
                  RARCH_LOG("[Lobby] filename match %s\n", playlist_entry->path);

                  if (i == 0)
                  {
                     state->content_path[0] = '\0';
                     strlcpy(state->content_path, playlist_entry->path, sizeof(state->content_path));
                  }
                  else
                  {
                     strlcat(state->content_path, "|", sizeof(state->content_path));
                     strlcat(state->content_path, playlist_entry->path, sizeof(state->content_path));
                  }

                  found[i] = true;
               }

               task_set_progress(task, (int)(j / playlist_size * 100.0));
            }

            playlist_free(playlist);
         }
      }

      for (i = 0; i < game_list->size; i++)
      {
         state->found = true;
         if (!found[i])
         {
            state->found = false;
            break;
         }
      }

      if (state->found)
      {
         RARCH_LOG("[Lobby] Subsystem matching set found %s\n", state->content_path);
         task_set_data(task, state);
         finish_task(task, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NETPLAY_COMPAT_CONTENT_FOUND));
      }

      string_list_free(state->lpl_list);
      string_list_free(game_list);
      return;
   }

   /* end of the line. no matches at all. */
   string_list_free(state->lpl_list);
   finish_task(task, "Failed to locate matching content by either CRC or filename.");
   command_event(CMD_EVENT_NETPLAY_INIT_DIRECT_DEFERRED, state->hostname);
   free(state);
}