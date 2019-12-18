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

/* Variables and functions */
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_LEFT ; 
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_MODE_DEFAULT ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_set_thumbnail_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_start_playlist_left_thumbnail_mode(unsigned type, const char *label)
{
   playlist_t *playlist = playlist_get_cached();

   if (!playlist)
      return -1;

   /* Set thumbnail_mode to default value */
   playlist_set_thumbnail_mode(playlist, PLAYLIST_THUMBNAIL_LEFT, PLAYLIST_THUMBNAIL_MODE_DEFAULT);
   playlist_write_file(playlist);

   return 0;
}