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
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {char const* subsystem_ident; char* core_path; char* core_name; char const* path; int /*<<< orphan*/  label; int /*<<< orphan*/  member_0; TYPE_2__* subsystem_roms; } ;
typedef  int /*<<< orphan*/  playlist_t ;
typedef  int /*<<< orphan*/  new_path ;
typedef  int /*<<< orphan*/  new_core_path ;
struct TYPE_14__ {int /*<<< orphan*/  db_playlist_file; } ;
typedef  TYPE_4__ menu_handle_t ;
struct TYPE_15__ {char* path; TYPE_3__* inf; } ;
typedef  TYPE_5__ core_info_ctx_find_t ;
struct TYPE_16__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ content_ctx_info_t ;
struct TYPE_13__ {char* display_name; } ;
struct TYPE_12__ {unsigned int size; TYPE_1__* elems; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLLECTION_SIZE ; 
 int /*<<< orphan*/  CORE_TYPE_PLAIN ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  PLAYLIST_LOAD ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int action_ok_file_load_with_detect_core_collection (char const*,char const*,unsigned int,size_t,size_t) ; 
 int /*<<< orphan*/  command_playlist_update_write (int /*<<< orphan*/ *,size_t,struct playlist_entry*) ; 
 int /*<<< orphan*/  content_add_subsystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  content_clear_subsystem () ; 
 int /*<<< orphan*/  content_set_subsystem_by_name (char const*) ; 
 int /*<<< orphan*/  core_info_find (TYPE_5__*,char*) ; 
 int default_action_ok_load_content_from_playlist_from_menu (char*,char*,int /*<<< orphan*/ ) ; 
 int menu_cbs_exit () ; 
 int /*<<< orphan*/  menu_content_playlist_load (int /*<<< orphan*/ *,size_t) ; 
 TYPE_4__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/  playlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 char* playlist_get_default_core_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,size_t,struct playlist_entry const**) ; 
 int /*<<< orphan*/ * playlist_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_resolve_path (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  task_push_load_new_core (char*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_push_load_subsystem_with_core_from_menu (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_ok_playlist_entry_collection(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   char new_path[PATH_MAX_LENGTH];
   char new_core_path[PATH_MAX_LENGTH];
   size_t selection_ptr                = 0;
   bool playlist_initialized           = false;
   playlist_t *playlist                = NULL;
   playlist_t *tmp_playlist            = NULL;
   const struct playlist_entry *entry  = NULL;
   unsigned i                          = 0;
   menu_handle_t *menu                 = menu_driver_get_ptr();

   if (!menu)
      return menu_cbs_exit();

   new_path[0]                         = '\0';
   new_core_path[0]                    = '\0';
   tmp_playlist                        = playlist_get_cached();

   if (!tmp_playlist)
   {
      tmp_playlist = playlist_init(
            menu->db_playlist_file, COLLECTION_SIZE);

      if (!tmp_playlist)
         return menu_cbs_exit();

      playlist_initialized = true;
   }

   playlist      = tmp_playlist;
   selection_ptr = entry_idx;

   playlist_get_index(playlist, selection_ptr, &entry);

   /* Subsystem codepath */
   if (!string_is_empty(entry->subsystem_ident))
   {
      content_ctx_info_t content_info = {0};

      task_push_load_new_core(entry->core_path, NULL,
            &content_info, CORE_TYPE_PLAIN, NULL, NULL);

      content_clear_subsystem();

      if (!content_set_subsystem_by_name(entry->subsystem_ident))
      {
         RARCH_LOG("[playlist] subsystem not found in implementation\n");
         /* TODO: Add OSD message telling users that content can't be loaded */
         return 0;
      }

      for (i = 0; i < entry->subsystem_roms->size; i++)
         content_add_subsystem(entry->subsystem_roms->elems[i].data);

      task_push_load_subsystem_with_core_from_menu(
         NULL, &content_info,
         CORE_TYPE_PLAIN, NULL, NULL);
      /* TODO: update playlist entry? move to first position I guess? */
      return 1;
   }

   /* Is the core path / name of the playlist entry not yet filled in? */
   if (     string_is_equal(entry->core_path, "DETECT")
         && string_is_equal(entry->core_name, "DETECT"))
   {
      core_info_ctx_find_t core_info;
      const char *entry_path                 = NULL;
      const char *default_core_path          =
            playlist_get_default_core_path(playlist);
      bool found_associated_core             = false;

      if (!string_is_empty(default_core_path))
      {
         strlcpy(new_core_path, default_core_path, sizeof(new_core_path));
         playlist_resolve_path(PLAYLIST_LOAD, new_core_path, sizeof(new_core_path));
         found_associated_core = true;
      }

      core_info.inf       = NULL;
      core_info.path      = new_core_path;

      if (!core_info_find(&core_info, new_core_path))
         found_associated_core = false;

      if (!found_associated_core)
      {
         /* TODO: figure out if this should refer to the inner or outer entry_path */
         /* TODO: make sure there's only one entry_path in this function */
         int ret = action_ok_file_load_with_detect_core_collection(entry_path,
               label, type, selection_ptr, entry_idx);
         if (playlist_initialized)
            playlist_free(tmp_playlist);
         return ret;
      }

      tmp_playlist = playlist_get_cached();

      if (tmp_playlist)
      {
         struct playlist_entry entry = {0};
         entry.core_path = (char*)default_core_path;
         entry.core_name = core_info.inf->display_name;

         command_playlist_update_write(
               tmp_playlist,
               selection_ptr,
               &entry);
      }
   }
   else
   {
      strlcpy(new_core_path, entry->core_path, sizeof(new_core_path));
       playlist_resolve_path(PLAYLIST_LOAD, new_core_path, sizeof(new_core_path));
   }

   if (!playlist || !menu_content_playlist_load(playlist, selection_ptr))
   {
      runloop_msg_queue_push(
            "File could not be loaded from playlist.\n",
            1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      if (playlist_initialized)
         playlist_free(tmp_playlist);
      return menu_cbs_exit();
   }

   playlist_get_index(playlist, selection_ptr, &entry);

   strlcpy(new_path, entry->path, sizeof(new_path));
   playlist_resolve_path(PLAYLIST_LOAD, new_path, sizeof(new_path));
   return default_action_ok_load_content_from_playlist_from_menu(
            new_core_path, new_path, entry->label);
}