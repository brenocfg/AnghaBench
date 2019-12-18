#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  menu_driver; } ;
struct TYPE_10__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_11__ {scalar_t__ state; } ;
typedef  TYPE_3__ retro_task_t ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_12__ {scalar_t__ list_index; int /*<<< orphan*/  thumbnail_path_data; scalar_t__ overwrite; int /*<<< orphan*/  left_thumbnail_exists; int /*<<< orphan*/  right_thumbnail_exists; int /*<<< orphan*/  playlist_path; } ;
typedef  TYPE_4__ pl_thumb_handle_t ;
struct TYPE_13__ {scalar_t__ rpl_entry_selection_ptr; } ;
typedef  TYPE_5__ menu_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_THUMBNAIL_LEFT ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_RIGHT ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_REFRESH_THUMBNAIL_IMAGE ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_5__* menu_driver_get_ptr () ; 
 scalar_t__ menu_navigation_get_selection () ; 
 scalar_t__ menu_thumbnail_get_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ menu_thumbnail_update_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int path_is_valid (char const*) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 char* playlist_get_conf_path (int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_empty (char*) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cb_task_pl_entry_thumbnail_refresh_menu(
      retro_task_t *task, void *task_data,
      void *user_data, const char *err)
{
#if defined(RARCH_INTERNAL) && defined(HAVE_MENU)
   
   pl_thumb_handle_t *pl_thumb     = NULL;
   const char *thumbnail_path      = NULL;
   const char *left_thumbnail_path = NULL;
   bool do_refresh                 = false;
   playlist_t *current_playlist    = playlist_get_cached();
   menu_handle_t *menu             = menu_driver_get_ptr();
   settings_t *settings            = config_get_ptr();
   
   if (!task || !settings)
      return;
   
   pl_thumb = (pl_thumb_handle_t*)task->state;
   if (!pl_thumb || !pl_thumb->thumbnail_path_data)
      return;
   
   /* Only refresh if current playlist hasn't changed,
    * and menu selection pointer is on the same entry
    * (Note: this is crude, but it's sufficient to prevent
    * 'refresh' from getting spammed when switching
    * playlists or scrolling through one playlist at
    * maximum speed with on demand downloads enabled)
    * NOTE: GLUI requires special treatment, since
    * it displays multiple thumbnails at a time... */
   
   if (!current_playlist)
      return;
   if (!menu)
      return;
   if (string_is_empty(playlist_get_conf_path(current_playlist)))
      return;
   
   if (string_is_equal(settings->arrays.menu_driver, "glui"))
   {
      if (!string_is_equal(pl_thumb->playlist_path,
            playlist_get_conf_path(current_playlist)))
         return;
   }
   else
   {
      if (((pl_thumb->list_index != menu_navigation_get_selection()) &&
           (pl_thumb->list_index != menu->rpl_entry_selection_ptr)) ||
            !string_is_equal(pl_thumb->playlist_path,
               playlist_get_conf_path(current_playlist)))
         return;
   }
   
   /* Only refresh if left/right thumbnails did not exist
    * when the task began, but do exist now
    * (with the caveat that we must also refresh if existing
    * files have been overwritten) */
   
   if (!pl_thumb->right_thumbnail_exists || pl_thumb->overwrite)
      if (menu_thumbnail_update_path(pl_thumb->thumbnail_path_data, MENU_THUMBNAIL_RIGHT))
         if (menu_thumbnail_get_path(pl_thumb->thumbnail_path_data, MENU_THUMBNAIL_RIGHT, &thumbnail_path))
            do_refresh = path_is_valid(thumbnail_path);
   
   if (!do_refresh)
      if (!pl_thumb->left_thumbnail_exists || pl_thumb->overwrite)
         if (menu_thumbnail_update_path(pl_thumb->thumbnail_path_data, MENU_THUMBNAIL_LEFT))
            if (menu_thumbnail_get_path(pl_thumb->thumbnail_path_data, MENU_THUMBNAIL_LEFT, &left_thumbnail_path))
               do_refresh = path_is_valid(left_thumbnail_path);
   
   if (do_refresh)
   {
      unsigned i = (unsigned)pl_thumb->list_index;
      menu_driver_ctl(RARCH_MENU_CTL_REFRESH_THUMBNAIL_IMAGE, &i);
   }
   
#endif
}