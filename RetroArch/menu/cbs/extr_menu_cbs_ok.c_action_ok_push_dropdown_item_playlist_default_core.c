#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_6__ {char* display_name; char* path; } ;
typedef  TYPE_1__ core_info_t ;
struct TYPE_7__ {size_t count; } ;
typedef  TYPE_2__ core_info_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NOT_AVAILABLE ; 
 int action_cancel_pop_default (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* core_info_get (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  core_info_get_list (TYPE_2__**) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_set_default_core_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  playlist_set_default_core_path (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static int action_ok_push_dropdown_item_playlist_default_core(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   core_info_list_t *core_info_list = NULL;
   playlist_t *playlist             = playlist_get_cached();
   const char* core_name            = path;

   (void)label;
   (void)type;
   (void)idx;
   (void)entry_idx;

   /* Get core list */
   core_info_get_list(&core_info_list);

   if (!core_info_list || !playlist)
      return -1;

   /* Handle N/A or empty path input */
   if (string_is_empty(core_name) ||
       string_is_equal(core_name, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NOT_AVAILABLE)))
   {
      playlist_set_default_core_path(playlist, "DETECT");
      playlist_set_default_core_name(playlist, "DETECT");
   }
   else
   {
      core_info_t *core_info = NULL;
      bool found             = false;
      size_t i;

      /* Loop through cores until we find a match */
      for (i = 0; i < core_info_list->count; i++)
      {
         core_info = NULL;
         core_info = core_info_get(core_info_list, i);

         if (core_info)
         {
            if (string_is_equal(core_name, core_info->display_name))
            {
               /* Update playlist */
               playlist_set_default_core_path(playlist, core_info->path);
               playlist_set_default_core_name(playlist, core_info->display_name);

               found = true;
               break;
            }
         }
      }

      /* Fallback... */
      if (!found)
      {
         playlist_set_default_core_path(playlist, "DETECT");
         playlist_set_default_core_name(playlist, "DETECT");
      }
   }

   /* In all cases, update file on disk */
   playlist_write_file(playlist);

   return action_cancel_pop_default(NULL, NULL, 0, 0);
}