#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {scalar_t__ runtime_status; char* runtime_str; char* last_played_str; int /*<<< orphan*/  last_played_second; int /*<<< orphan*/  last_played_minute; int /*<<< orphan*/  last_played_hour; int /*<<< orphan*/  last_played_day; int /*<<< orphan*/  last_played_month; int /*<<< orphan*/  last_played_year; int /*<<< orphan*/  runtime_seconds; int /*<<< orphan*/  runtime_minutes; int /*<<< orphan*/  runtime_hours; int /*<<< orphan*/  core_path; int /*<<< orphan*/  path; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  menu_driver; } ;
struct TYPE_5__ {scalar_t__ playlist_sublabel_runtime_type; scalar_t__ playlist_sublabel_last_played_style; } ;
struct TYPE_7__ {TYPE_2__ arrays; TYPE_1__ uints; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  runtime_str ;
typedef  int /*<<< orphan*/  runtime_log_t ;
typedef  int /*<<< orphan*/  playlist_t ;
typedef  int /*<<< orphan*/  last_played_str ;
typedef  enum playlist_sublabel_last_played_style_type { ____Placeholder_playlist_sublabel_last_played_style_type } playlist_sublabel_last_played_style_type ;

/* Variables and functions */
 int PLAYLIST_LAST_PLAYED_STYLE_YMD_HMS ; 
 scalar_t__ PLAYLIST_RUNTIME_MISSING ; 
 scalar_t__ PLAYLIST_RUNTIME_PER_CORE ; 
 scalar_t__ PLAYLIST_RUNTIME_VALID ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,size_t,struct playlist_entry const**) ; 
 size_t playlist_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_update_runtime (int /*<<< orphan*/ *,size_t,struct playlist_entry*,int) ; 
 int /*<<< orphan*/  runtime_log_get_last_played (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runtime_log_get_last_played_str (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  runtime_log_get_runtime_hms (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runtime_log_get_runtime_str (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ runtime_log_has_runtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * runtime_log_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 

void runtime_update_playlist(playlist_t *playlist, size_t idx)
{
   settings_t *settings               = config_get_ptr();
   runtime_log_t *runtime_log         = NULL;
   const struct playlist_entry *entry = NULL;
   struct playlist_entry update_entry = {0};
   enum playlist_sublabel_last_played_style_type timedate_style;
   char runtime_str[64];
   char last_played_str[64];
   
   /* Sanity check */
   if (!playlist || !settings)
      return;
   
   if (idx >= playlist_get_size(playlist))
      return;
   
   /* Set fallback playlist 'runtime_status'
    * (saves 'if' checks later...) */
   update_entry.runtime_status = PLAYLIST_RUNTIME_MISSING;
   
   /* Get current last played formatting type
    * > Have to include a 'HAVE_MENU' check here... */
#ifdef HAVE_MENU
   timedate_style = (enum playlist_sublabel_last_played_style_type)settings->uints.playlist_sublabel_last_played_style;
#else
   timedate_style = PLAYLIST_LAST_PLAYED_STYLE_YMD_HMS;
#endif

   /* 'Attach' runtime/last played strings */
   runtime_str[0]               = '\0';
   last_played_str[0]           = '\0';
   update_entry.runtime_str     = runtime_str;
   update_entry.last_played_str = last_played_str;
   
   /* Read current playlist entry */
   playlist_get_index(playlist, idx, &entry);
   
   /* Attempt to open log file */
   runtime_log = runtime_log_init(entry->path, entry->core_path,
         (settings->uints.playlist_sublabel_runtime_type == PLAYLIST_RUNTIME_PER_CORE));
   
   if (runtime_log)
   {
      /* Check whether a non-zero runtime has been recorded */
      if (runtime_log_has_runtime(runtime_log))
      {
         /* Read current runtime */
         runtime_log_get_runtime_hms(runtime_log,
               &update_entry.runtime_hours, &update_entry.runtime_minutes, &update_entry.runtime_seconds);
         
         runtime_log_get_runtime_str(runtime_log, runtime_str, sizeof(runtime_str));
         
         /* Read last played timestamp */
         runtime_log_get_last_played(runtime_log,
               &update_entry.last_played_year, &update_entry.last_played_month, &update_entry.last_played_day,
               &update_entry.last_played_hour, &update_entry.last_played_minute, &update_entry.last_played_second);
         
         runtime_log_get_last_played_str(runtime_log, last_played_str, sizeof(last_played_str), timedate_style);
         
         /* Playlist entry now contains valid runtime data */
         update_entry.runtime_status = PLAYLIST_RUNTIME_VALID;
      }
      
      /* Clean up */
      free(runtime_log);
   }
   
   /* Ozone requires runtime/last played strings to be
    * populated even when no runtime is recorded */
   if (string_is_equal(settings->arrays.menu_driver, "ozone"))
   {
      if (update_entry.runtime_status != PLAYLIST_RUNTIME_VALID)
      {
         runtime_log_get_runtime_str(NULL, runtime_str, sizeof(runtime_str));
         runtime_log_get_last_played_str(NULL, last_played_str, sizeof(last_played_str), timedate_style);
      }
   }
   
   /* Update playlist */
   playlist_update_runtime(playlist, idx, &update_entry, false);
}