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
struct playlist_entry {int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_3__ {scalar_t__ rpl_entry_selection_ptr; int /*<<< orphan*/  deferred_path; } ;
typedef  TYPE_1__ menu_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_CTL_IS_DUMMY_CORE ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,scalar_t__,struct playlist_entry const**) ; 
 scalar_t__ playlist_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int string_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool history_needs_navigation_clear(menu_handle_t *menu, playlist_t *playlist)
{
   if (!menu)
      return false;

   /* If content is running, compare last selected path
    * with current content path */
   if (!rarch_ctl(RARCH_CTL_IS_DUMMY_CORE, NULL))
      return string_is_equal(menu->deferred_path, path_get(RARCH_PATH_CONTENT));

   /* If content is not running, have to examine the
    * playlist... */
   if (!playlist)
      return false;

   if (menu->rpl_entry_selection_ptr < playlist_size(playlist))
   {
      const struct playlist_entry *entry = NULL;

      playlist_get_index(playlist, menu->rpl_entry_selection_ptr, &entry);
      return !string_is_equal(menu->deferred_path, entry->path);
   }

   return false;
}