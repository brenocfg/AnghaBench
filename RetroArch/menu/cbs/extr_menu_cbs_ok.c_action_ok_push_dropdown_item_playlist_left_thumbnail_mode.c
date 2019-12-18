#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  playlist_t ;
typedef  enum playlist_thumbnail_mode { ____Placeholder_playlist_thumbnail_mode } playlist_thumbnail_mode ;

/* Variables and functions */
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_LEFT ; 
 int action_cancel_pop_default (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_set_thumbnail_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_ok_push_dropdown_item_playlist_left_thumbnail_mode(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   playlist_t *playlist = playlist_get_cached();

   if (!playlist)
      return -1;

   playlist_set_thumbnail_mode(playlist, PLAYLIST_THUMBNAIL_LEFT, (enum playlist_thumbnail_mode)idx);
   playlist_write_file(playlist);

   return action_cancel_pop_default(NULL, NULL, 0, 0);
}