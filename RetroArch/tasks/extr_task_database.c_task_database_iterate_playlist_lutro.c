#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {char* path; char* label; char* core_path; char* core_name; char* db_name; char* crc32; scalar_t__ last_played_second; scalar_t__ last_played_minute; scalar_t__ last_played_hour; scalar_t__ last_played_day; scalar_t__ last_played_month; scalar_t__ last_played_year; scalar_t__ runtime_seconds; scalar_t__ runtime_minutes; scalar_t__ runtime_hours; int /*<<< orphan*/ * subsystem_roms; int /*<<< orphan*/ * subsystem_name; int /*<<< orphan*/ * subsystem_ident; } ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_3__ {int /*<<< orphan*/  playlist_directory; } ;
typedef  TYPE_1__ db_handle_t ;
typedef  int /*<<< orphan*/  database_state_handle_t ;
typedef  int /*<<< orphan*/  database_info_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  COLLECTION_SIZE ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  fill_pathname_join (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fill_short_pathname_representation_noext (char*,char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  playlist_entry_exists (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  playlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * playlist_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_push (int /*<<< orphan*/ *,struct playlist_entry*) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int task_database_iterate_playlist_lutro(
      db_handle_t *_db,
      database_state_handle_t *db_state,
      database_info_handle_t *db,
      const char *path)
{
   char *db_playlist_path  = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   playlist_t   *playlist  = NULL;

   db_playlist_path[0]     = '\0';

   if (!string_is_empty(_db->playlist_directory))
      fill_pathname_join(db_playlist_path,
            _db->playlist_directory,
            "Lutro.lpl",
            PATH_MAX_LENGTH * sizeof(char));

   playlist = playlist_init(db_playlist_path, COLLECTION_SIZE);

   free(db_playlist_path);

   if (!playlist_entry_exists(playlist,
            path, "DETECT"))
   {
      struct playlist_entry entry;
      char *game_title            = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

      game_title[0] = '\0';

      fill_short_pathname_representation_noext(game_title,
            path, PATH_MAX_LENGTH * sizeof(char));

      /* the push function reads our entry as const, so these casts are safe */
      entry.path              = (char*)path;
      entry.label             = game_title;
      entry.core_path         = (char*)"DETECT";
      entry.core_name         = (char*)"DETECT";
      entry.db_name           = (char*)"Lutro.lpl";
      entry.crc32             = (char*)"DETECT";
      entry.subsystem_ident   = NULL;
      entry.subsystem_name    = NULL;
      entry.subsystem_roms    = NULL;
      entry.runtime_hours     = 0;
      entry.runtime_minutes   = 0;
      entry.runtime_seconds   = 0;
      entry.last_played_year  = 0;
      entry.last_played_month = 0;
      entry.last_played_day   = 0;
      entry.last_played_hour  = 0;
      entry.last_played_minute= 0;
      entry.last_played_second= 0;

      playlist_push(playlist, &entry);

      free(game_title);
   }

   playlist_write_file(playlist);
   playlist_free(playlist);

   return 0;
}