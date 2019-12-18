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
struct playlist_entry {char* core_path; char* path; char* runtime_str; char* last_played_str; int /*<<< orphan*/  last_played_second; int /*<<< orphan*/  last_played_minute; int /*<<< orphan*/  last_played_hour; int /*<<< orphan*/  last_played_day; int /*<<< orphan*/  last_played_month; int /*<<< orphan*/  last_played_year; int /*<<< orphan*/  runtime_seconds; int /*<<< orphan*/  runtime_minutes; int /*<<< orphan*/  runtime_hours; int /*<<< orphan*/  runtime_status; } ;
typedef  int /*<<< orphan*/  real_path ;
typedef  int /*<<< orphan*/  real_core_path ;
struct TYPE_3__ {size_t size; int cap; int modified; struct playlist_entry* entries; } ;
typedef  TYPE_1__ playlist_t ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  memmove (struct playlist_entry*,struct playlist_entry*,int) ; 
 int /*<<< orphan*/  path_resolve_realpath (char*,int,int) ; 
 int /*<<< orphan*/  playlist_core_path_equal (char*,char*) ; 
 int /*<<< orphan*/  playlist_free_entry (struct playlist_entry*) ; 
 scalar_t__ playlist_path_equal (char*,char const*) ; 
 void* strdup (char*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

bool playlist_push_runtime(playlist_t *playlist,
      const struct playlist_entry *entry)
{
   size_t i;
   char real_path[PATH_MAX_LENGTH];
   char real_core_path[PATH_MAX_LENGTH];

   real_path[0] = '\0';
   real_core_path[0] = '\0';

   if (!playlist || !entry)
      return false;

   if (string_is_empty(entry->core_path))
   {
      RARCH_ERR("cannot push NULL or empty core path into the playlist.\n");
      return false;
   }

   /* Get 'real' path */
   if (!string_is_empty(entry->path))
   {
      strlcpy(real_path, entry->path, sizeof(real_path));
      path_resolve_realpath(real_path, sizeof(real_path), true);
   }

   /* Get 'real' core path */
   strlcpy(real_core_path, entry->core_path, sizeof(real_core_path));
   if (!string_is_equal(real_core_path, "DETECT"))
      path_resolve_realpath(real_core_path, sizeof(real_core_path), true);

   if (string_is_empty(real_core_path))
   {
      RARCH_ERR("cannot push NULL or empty core path into the playlist.\n");
      return false;
   }

   for (i = 0; i < playlist->size; i++)
   {
      struct playlist_entry tmp;
      const char *entry_path = playlist->entries[i].path;
      bool equal_path        =
         (string_is_empty(real_path) && string_is_empty(entry_path)) ||
         playlist_path_equal(real_path, entry_path);

      /* Core name can have changed while still being the same core.
       * Differentiate based on the core path only. */
      if (!equal_path)
         continue;

      if (!playlist_core_path_equal(real_core_path, playlist->entries[i].core_path))
         continue;

      /* If top entry, we don't want to push a new entry since
       * the top and the entry to be pushed are the same. */
      if (i == 0)
         return false;

      /* Seen it before, bump to top. */
      tmp = playlist->entries[i];
      memmove(playlist->entries + 1, playlist->entries,
            i * sizeof(struct playlist_entry));
      playlist->entries[0] = tmp;

      goto success;
   }

   if (playlist->size == playlist->cap)
   {
      struct playlist_entry *last_entry = &playlist->entries[playlist->cap - 1];

      if (last_entry)
         playlist_free_entry(last_entry);
      playlist->size--;
   }

   if (playlist->entries)
   {
      memmove(playlist->entries + 1, playlist->entries,
            (playlist->cap - 1) * sizeof(struct playlist_entry));

      playlist->entries[0].path            = NULL;
      playlist->entries[0].core_path       = NULL;

      if (!string_is_empty(real_path))
         playlist->entries[0].path      = strdup(real_path);
      if (!string_is_empty(real_core_path))
         playlist->entries[0].core_path = strdup(real_core_path);

      playlist->entries[0].runtime_status = entry->runtime_status;
      playlist->entries[0].runtime_hours = entry->runtime_hours;
      playlist->entries[0].runtime_minutes = entry->runtime_minutes;
      playlist->entries[0].runtime_seconds = entry->runtime_seconds;
      playlist->entries[0].last_played_year = entry->last_played_year;
      playlist->entries[0].last_played_month = entry->last_played_month;
      playlist->entries[0].last_played_day = entry->last_played_day;
      playlist->entries[0].last_played_hour = entry->last_played_hour;
      playlist->entries[0].last_played_minute = entry->last_played_minute;
      playlist->entries[0].last_played_second = entry->last_played_second;

      playlist->entries[0].runtime_str        = NULL;
      playlist->entries[0].last_played_str    = NULL;

      if (!string_is_empty(entry->runtime_str))
         playlist->entries[0].runtime_str     = strdup(entry->runtime_str);
      if (!string_is_empty(entry->last_played_str))
         playlist->entries[0].last_played_str = strdup(entry->last_played_str);
   }

   playlist->size++;

success:
   playlist->modified = true;

   return true;
}