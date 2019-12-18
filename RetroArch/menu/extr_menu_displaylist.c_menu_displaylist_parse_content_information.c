#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct playlist_entry {char* label; char* path; char* core_path; char* db_name; char* core_name; } ;
struct TYPE_15__ {int /*<<< orphan*/  path_content_database; } ;
struct TYPE_14__ {scalar_t__ playlist_sublabel_runtime_type; scalar_t__ playlist_sublabel_last_played_style; } ;
struct TYPE_13__ {int /*<<< orphan*/  content_runtime_log_aggregate; scalar_t__ content_runtime_log; } ;
struct TYPE_17__ {TYPE_3__ paths; TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_5__ settings_t ;
typedef  int /*<<< orphan*/  runtime_log_t ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_18__ {unsigned int rpl_entry_selection_ptr; char* deferred_path; } ;
typedef  TYPE_6__ menu_handle_t ;
struct TYPE_19__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_7__ menu_displaylist_info_t ;
typedef  enum playlist_sublabel_last_played_style_type { ____Placeholder_playlist_sublabel_last_played_style_type } playlist_sublabel_last_played_style_type ;
typedef  int /*<<< orphan*/  db_path ;
typedef  int /*<<< orphan*/  db_name_no_ext_buff ;
typedef  int /*<<< orphan*/  core_name ;
struct TYPE_20__ {char const* path; TYPE_4__* inf; } ;
typedef  TYPE_8__ core_info_ctx_find_t ;
struct TYPE_16__ {char const* display_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TYPE_RDB_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CONTENT_INFO_CORE_NAME ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CONTENT_INFO_DATABASE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CONTENT_INFO_LABEL ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CONTENT_INFO_LAST_PLAYED ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CONTENT_INFO_PATH ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CONTENT_INFO_RUNTIME ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_RDB_ENTRY_DETAIL ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CONTENT_INFO_CORE_NAME ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CONTENT_INFO_DATABASE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CONTENT_INFO_LABEL ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CONTENT_INFO_PATH ; 
 int PATH_MAX_LENGTH ; 
 scalar_t__ PLAYLIST_RUNTIME_AGGREGATE ; 
 scalar_t__ PLAYLIST_RUNTIME_PER_CORE ; 
 int /*<<< orphan*/  RARCH_CTL_IS_DUMMY_CORE ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 TYPE_5__* config_get_ptr () ; 
 scalar_t__ core_info_find (TYPE_8__*,char const*) ; 
 int /*<<< orphan*/  fill_pathname_join_noext (char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ menu_entries_append_enum (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_valid (char*) ; 
 char* path_remove_extension (char*) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,unsigned int,struct playlist_entry const**) ; 
 int playlist_index_is_valid (int /*<<< orphan*/ *,unsigned int,char const*,char const*) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runtime_log_get_last_played_str (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  runtime_log_get_runtime_str (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ runtime_log_has_runtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * runtime_log_init (char const*,char const*,int) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char*,char const*) ; 
 int strlcat (char*,char const*,int) ; 
 int strlcpy (char*,char const*,int) ; 

__attribute__((used)) static unsigned menu_displaylist_parse_content_information(
      menu_handle_t *menu,
      menu_displaylist_info_t *info)
{
   settings_t *settings                = config_get_ptr();
   playlist_t *playlist                = playlist_get_cached();
   unsigned idx                        = menu->rpl_entry_selection_ptr;
   const struct playlist_entry *entry  = NULL;
   const char *loaded_content_path     = path_get(RARCH_PATH_CONTENT);
   const char *loaded_core_path        = path_get(RARCH_PATH_CORE);
   const char *content_label           = NULL;
   const char *content_path            = NULL;
   const char *core_path               = NULL;
   const char *db_name                 = NULL;
   bool content_loaded                 = false;
   bool playlist_valid                 = false;
   unsigned count                      = 0;
   int n                               = 0;
   char core_name[PATH_MAX_LENGTH];
   char tmp[8192];

   core_name[0] = '\0';

   if (!settings)
      return count;

   content_loaded = !rarch_ctl(RARCH_CTL_IS_DUMMY_CORE, NULL)
         && string_is_equal(menu->deferred_path, loaded_content_path);

   /* If content is currently running, have to make sure
    * we have a valid playlist to work with
    * (if content is not running, than playlist will always
    * be valid provided that playlist_get_cached() does not
    * return NULL) */
   if (content_loaded)
   {
      if (!string_is_empty(loaded_content_path) && !string_is_empty(loaded_core_path))
         playlist_valid = playlist_index_is_valid(
               playlist, idx, loaded_content_path, loaded_core_path);
   }
   else if (playlist)
      playlist_valid = true;

   if (playlist_valid)
   {
      /* If playlist is valid, all information is readily available */
      playlist_get_index(playlist, idx, &entry);

      if (entry)
      {
         content_label = entry->label;
         content_path  = entry->path;
         core_path     = entry->core_path;
         db_name       = entry->db_name;

         strlcpy(core_name, entry->core_name, sizeof(core_name));
      }
   }
   else
   {
      core_info_ctx_find_t core_info;

      /* No playlist - just extract what we can... */
      content_path   = loaded_content_path;
      core_path      = loaded_core_path;

      core_info.inf  = NULL;
      core_info.path = core_path;

      if (core_info_find(&core_info, core_path))
         if (!string_is_empty(core_info.inf->display_name))
            strlcpy(core_name, core_info.inf->display_name, sizeof(core_name));
   }

   /* Content label */
   if (!string_is_empty(content_label))
   {
      tmp[0]   = '\0';

      n        = strlcpy(tmp, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CONTENT_INFO_LABEL), sizeof(tmp));
      strlcat(tmp, ": ", sizeof(tmp));
      n        = strlcat(tmp, content_label, sizeof(tmp));

      /* Silence gcc compiler warning
       * (getting so sick of these...) */
      if ((n < 0) || (n >= PATH_MAX_LENGTH))
         n = 0;

      if (menu_entries_append_enum(info->list, tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_CONTENT_INFO_LABEL),
            MENU_ENUM_LABEL_CONTENT_INFO_LABEL,
            0, 0, 0))
         count++;
   }

   /* Content path */
   if (!string_is_empty(content_path))
   {
      tmp[0]   = '\0';

      n        = strlcpy(tmp, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CONTENT_INFO_PATH), sizeof(tmp));
      n        = strlcat(tmp, ": ", sizeof(tmp));
      n        = strlcat(tmp, content_path, sizeof(tmp));

      /* Silence gcc compiler warning
       * (getting so sick of these...) */
      if ((n < 0) || (n >= PATH_MAX_LENGTH))
         n = 0;

      if (menu_entries_append_enum(info->list, tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_CONTENT_INFO_PATH),
            MENU_ENUM_LABEL_CONTENT_INFO_PATH,
            0, 0, 0))
         count++;
   }

   /* Core name */
   if (!string_is_empty(core_name) &&
       !string_is_equal(core_name, "DETECT"))
   {
      tmp[0]   = '\0';

      n        = strlcpy(tmp, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CONTENT_INFO_CORE_NAME), sizeof(tmp));
      n        = strlcat(tmp, ": ", sizeof(tmp));
      n        = strlcat(tmp, core_name, sizeof(tmp));

      /* Silence gcc compiler warning
       * (getting so sick of these...) */
      if ((n < 0) || (n >= PATH_MAX_LENGTH))
         n = 0;

      if (menu_entries_append_enum(info->list, tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_CONTENT_INFO_CORE_NAME),
            MENU_ENUM_LABEL_CONTENT_INFO_CORE_NAME,
            0, 0, 0))
         count++;
   }

   /* Database */
   if (!string_is_empty(db_name))
   {
      char *db_name_no_ext = NULL;
      char db_name_no_ext_buff[PATH_MAX_LENGTH];

      db_name_no_ext_buff[0] = '\0';

      /* Remove .lpl extension
       * > path_remove_extension() requires a char * (not const)
       *   so have to use a temporary buffer... */
      strlcpy(db_name_no_ext_buff, db_name, sizeof(db_name_no_ext_buff));
      db_name_no_ext = path_remove_extension(db_name_no_ext_buff);

      if (!string_is_empty(db_name_no_ext))
      {
         tmp[0]   = '\0';

         n        = strlcpy(tmp, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CONTENT_INFO_DATABASE), sizeof(tmp));
         n        = strlcat(tmp, ": ", sizeof(tmp));
         n        = strlcat(tmp, db_name_no_ext, sizeof(tmp));

         /* Silence gcc compiler warning
          * (getting so sick of these...) */
         if ((n < 0) || (n >= PATH_MAX_LENGTH))
            n = 0;

         if (menu_entries_append_enum(info->list, tmp,
               msg_hash_to_str(MENU_ENUM_LABEL_CONTENT_INFO_DATABASE),
               MENU_ENUM_LABEL_CONTENT_INFO_DATABASE,
               0, 0, 0))
            count++;
      }
   }

   /* Runtime */
   if (((settings->uints.playlist_sublabel_runtime_type == PLAYLIST_RUNTIME_PER_CORE) &&
         settings->bools.content_runtime_log) ||
       ((settings->uints.playlist_sublabel_runtime_type == PLAYLIST_RUNTIME_AGGREGATE) &&
         !settings->bools.content_runtime_log_aggregate))
   {
      runtime_log_t *runtime_log = runtime_log_init(
            content_path, core_path,
            (settings->uints.playlist_sublabel_runtime_type == PLAYLIST_RUNTIME_PER_CORE));

      if (runtime_log)
      {
         if (runtime_log_has_runtime(runtime_log))
         {
            /* Play time */
            tmp[0] = '\0';
            runtime_log_get_runtime_str(runtime_log, tmp, sizeof(tmp));

            if (!string_is_empty(tmp))
               if (menu_entries_append_enum(info->list, tmp,
                     msg_hash_to_str(MENU_ENUM_LABEL_CONTENT_INFO_RUNTIME),
                     MENU_ENUM_LABEL_CONTENT_INFO_RUNTIME,
                     0, 0, 0))
                  count++;

            /* Last Played */
            tmp[0] = '\0';
            runtime_log_get_last_played_str(runtime_log, tmp, sizeof(tmp),
                  (enum playlist_sublabel_last_played_style_type)settings->uints.playlist_sublabel_last_played_style);

            if (!string_is_empty(tmp))
               if (menu_entries_append_enum(info->list, tmp,
                     msg_hash_to_str(MENU_ENUM_LABEL_CONTENT_INFO_LAST_PLAYED),
                     MENU_ENUM_LABEL_CONTENT_INFO_LAST_PLAYED,
                     0, 0, 0))
                  count++;
         }

         free(runtime_log);
      }
   }

#ifdef HAVE_LIBRETRODB

   /* Database entry */
   if (!string_is_empty(content_label) && !string_is_empty(db_name))
   {
      char db_path[PATH_MAX_LENGTH];

      db_path[0] = '\0';

      fill_pathname_join_noext(db_path,
            settings->paths.path_content_database,
            db_name,
            sizeof(db_path));
      strlcat(db_path, ".rdb", sizeof(db_path));

      if (path_is_valid(db_path))
         if (menu_entries_append_enum(info->list,
               content_label,
               db_path,
               MENU_ENUM_LABEL_RDB_ENTRY_DETAIL,
               FILE_TYPE_RDB_ENTRY, 0, 0))
            count++;
   }

#endif

   return count;
}