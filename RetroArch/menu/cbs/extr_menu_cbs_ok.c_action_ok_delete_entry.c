#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_4__ {int /*<<< orphan*/  rpl_entry_selection_ptr; } ;
typedef  TYPE_1__ menu_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/ * content_favorites; int /*<<< orphan*/ * image_history; int /*<<< orphan*/ * video_history; int /*<<< orphan*/ * music_history; int /*<<< orphan*/ * content_history; } ;

/* Variables and functions */
 TYPE_3__ g_defaults ; 
 int menu_cbs_exit () ; 
 TYPE_1__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/  menu_entries_pop_stack (size_t*,int /*<<< orphan*/ ,int) ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  menu_navigation_set_selection (size_t) ; 
 int /*<<< orphan*/  playlist_delete_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 char* playlist_get_conf_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_equal (char*,char*) ; 

__attribute__((used)) static int action_ok_delete_entry(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   size_t new_selection_ptr;
   char *conf_path           = NULL;
   char *def_conf_path       = NULL;
   char *def_conf_music_path = NULL;
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
   char *def_conf_video_path = NULL;
#endif
#ifdef HAVE_IMAGEVIEWER
   char *def_conf_img_path   = NULL;
#endif
   char *def_conf_fav_path   = NULL;
   playlist_t *playlist      = playlist_get_cached();
   menu_handle_t *menu       = menu_driver_get_ptr();

   if (!menu)
      return menu_cbs_exit();

   conf_path                 = playlist_get_conf_path(playlist);
   def_conf_path             = playlist_get_conf_path(g_defaults.content_history);
   def_conf_music_path       = playlist_get_conf_path(g_defaults.music_history);
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
   def_conf_video_path       = playlist_get_conf_path(g_defaults.video_history);
#endif
#ifdef HAVE_IMAGEVIEWER
   def_conf_img_path         = playlist_get_conf_path(g_defaults.image_history);
#endif
   def_conf_fav_path         = playlist_get_conf_path(g_defaults.content_favorites);

   if (string_is_equal(conf_path, def_conf_path))
      playlist = g_defaults.content_history;
   else if (string_is_equal(conf_path, def_conf_music_path))
      playlist = g_defaults.music_history;
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
   else if (string_is_equal(conf_path, def_conf_video_path))
      playlist = g_defaults.video_history;
#endif
#ifdef HAVE_IMAGEVIEWER
   else if (string_is_equal(conf_path, def_conf_img_path))
      playlist = g_defaults.image_history;
#endif
   else if (string_is_equal(conf_path, def_conf_fav_path))
      playlist = g_defaults.content_favorites;

   if (playlist)
   {
      playlist_delete_index(playlist, menu->rpl_entry_selection_ptr);
      playlist_write_file(playlist);
   }

   new_selection_ptr = menu_navigation_get_selection();
   menu_entries_pop_stack(&new_selection_ptr, 0, 1);
   menu_navigation_set_selection(new_selection_ptr);

   return 0;
}