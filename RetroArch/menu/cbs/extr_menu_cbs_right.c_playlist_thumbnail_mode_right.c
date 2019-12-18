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
typedef  enum playlist_thumbnail_id { ____Placeholder_playlist_thumbnail_id } playlist_thumbnail_id ;

/* Variables and functions */
 int PLAYLIST_THUMBNAIL_MODE_BOXARTS ; 
 int PLAYLIST_THUMBNAIL_MODE_DEFAULT ; 
 int playlist_get_thumbnail_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  playlist_set_thumbnail_mode (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void playlist_thumbnail_mode_right(playlist_t *playlist, enum playlist_thumbnail_id thumbnail_id,
      bool wraparound)
{
   enum playlist_thumbnail_mode thumbnail_mode =
         playlist_get_thumbnail_mode(playlist, thumbnail_id);

   if (thumbnail_mode < PLAYLIST_THUMBNAIL_MODE_BOXARTS)
      thumbnail_mode = (enum playlist_thumbnail_mode)((unsigned)thumbnail_mode + 1);
   else if (wraparound)
      thumbnail_mode = PLAYLIST_THUMBNAIL_MODE_DEFAULT;

   playlist_set_thumbnail_mode(playlist, thumbnail_id, thumbnail_mode);
   playlist_write_file(playlist);
}