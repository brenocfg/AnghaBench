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
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_LEFT ; 
 char const* get_playlist_thumbnail_mode_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_playlist_left_thumbnail_mode(
      file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   playlist_t *playlist  = playlist_get_cached();

   *s = '\0';
   *w = 19;

   strlcpy(s2, path, len2);

   if (!playlist)
      return;

   strlcpy(
         s,
         get_playlist_thumbnail_mode_value(playlist, PLAYLIST_THUMBNAIL_LEFT),
         len);
}