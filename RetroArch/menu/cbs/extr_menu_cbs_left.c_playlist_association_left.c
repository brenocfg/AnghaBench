#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  playlist_t ;
typedef  int /*<<< orphan*/  core_path ;
struct TYPE_7__ {int /*<<< orphan*/  display_name; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ core_info_t ;
struct TYPE_8__ {size_t count; } ;
typedef  TYPE_2__ core_info_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_INFO_LIST_SORT_DISPLAY_NAME ; 
 int PATH_MAX_LENGTH ; 
 TYPE_1__* core_info_get (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  core_info_get_list (TYPE_2__**) ; 
 int /*<<< orphan*/  core_info_qsort (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int menu_cbs_exit () ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_get_default_core_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_set_default_core_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_set_default_core_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int playlist_association_left(unsigned type, const char *label,
      bool wraparound)
{
   char core_path[PATH_MAX_LENGTH];
   size_t i, next, current          = 0;
   playlist_t *playlist             = playlist_get_cached();
   core_info_list_t *core_info_list = NULL;
   core_info_t *core_info           = NULL;

   core_path[0]     = '\0';

   if (!playlist)
      return -1;

   core_info_get_list(&core_info_list);
   if (!core_info_list)
      return menu_cbs_exit();

   /* Get current core path association */
   if (string_is_empty(playlist_get_default_core_path(playlist)))
   {
      core_path[0] = 'D';
      core_path[1] = 'E';
      core_path[2] = 'T';
      core_path[3] = 'E';
      core_path[4] = 'C';
      core_path[5] = 'T';
      core_path[6] = '\0';
   }
   else
      strlcpy(core_path, playlist_get_default_core_path(playlist), sizeof(core_path));

   /* Sort cores alphabetically */
   core_info_qsort(core_info_list, CORE_INFO_LIST_SORT_DISPLAY_NAME);

   /* Get the index of the currently associated core */
   for (i = 0; i < core_info_list->count; i++)
   {
      core_info = NULL;
      core_info = core_info_get(core_info_list, i);
      if (!core_info)
         return -1;
      if (string_is_equal(core_info->path, core_path))
         current = i;
   }

   /* Decrement core index */
   if (current > 0)
      next = current - 1;
   else if (wraparound && (core_info_list->count > 1))
      next = core_info_list->count - 1;
   else
      next = 0; /* Silence 'next' may be used uninitialized warning */

   /* Get new core info */
   core_info = NULL;
   core_info = core_info_get(core_info_list, next);
   if (!core_info)
      return -1;

   /* Update playlist */
   playlist_set_default_core_path(playlist, core_info->path);
   playlist_set_default_core_name(playlist, core_info->display_name);
   playlist_write_file(playlist);

   return 0;
}