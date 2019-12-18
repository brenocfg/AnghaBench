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
typedef  int /*<<< orphan*/  menu_handle_t ;
typedef  int /*<<< orphan*/  menu_displaylist_info_t ;

/* Variables and functions */
 int menu_displaylist_parse_playlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  menu_displaylist_set_new_playlist (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_qsort (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_displaylist_parse_playlist_generic(
      menu_handle_t *menu,
      menu_displaylist_info_t *info,
      const char *playlist_name,
      const char *playlist_path,
      bool is_collection,
      bool sort,
      int *ret)
{
   playlist_t *playlist = NULL;

   menu_displaylist_set_new_playlist(menu, playlist_path);

   playlist             = playlist_get_cached();

   if (!playlist)
      return;

   if (sort)
      playlist_qsort(playlist);

   *ret              = menu_displaylist_parse_playlist(info,
         playlist, playlist_name, is_collection);
}