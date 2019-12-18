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
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_RIGHT ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_thumbnail_mode_left (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int playlist_right_thumbnail_mode_left(unsigned type, const char *label,
      bool wraparound)
{
   playlist_t *playlist = playlist_get_cached();

   if (!playlist)
      return -1;

   playlist_thumbnail_mode_left(playlist, PLAYLIST_THUMBNAIL_RIGHT, wraparound);

   return 0;
}