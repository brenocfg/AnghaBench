#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ menu_rgui_inline_thumbnails; } ;
struct TYPE_10__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_11__ {scalar_t__ is_playlist; int /*<<< orphan*/  thumbnail_path_data; scalar_t__ show_fs_thumbnail; } ;
typedef  TYPE_3__ rgui_t ;
struct TYPE_14__ {int is_valid; char* path; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_13__ {int is_valid; char* path; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_12__ {int is_valid; char* path; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_THUMBNAIL_LEFT ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_RIGHT ; 
 TYPE_2__* config_get_ptr () ; 
 TYPE_7__ fs_thumbnail ; 
 scalar_t__ menu_thumbnail_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ mini_left_thumbnail ; 
 TYPE_5__ mini_thumbnail ; 
 int /*<<< orphan*/  rgui_scan_selected_entry_thumbnail (TYPE_3__*,int) ; 

__attribute__((used)) static void rgui_refresh_thumbnail_image(void *userdata, unsigned i)
{
   rgui_t *rgui         = (rgui_t*)userdata;
   settings_t *settings = config_get_ptr();
   if (!rgui || !settings)
      return;

   /* Only refresh thumbnails if thumbnails are enabled */
   if ((rgui->show_fs_thumbnail || settings->bools.menu_rgui_inline_thumbnails) &&
       (menu_thumbnail_is_enabled(rgui->thumbnail_path_data, MENU_THUMBNAIL_RIGHT) ||
        menu_thumbnail_is_enabled(rgui->thumbnail_path_data, MENU_THUMBNAIL_LEFT)))
   {
      /* In all cases, reset current thumbnails */
      fs_thumbnail.width = 0;
      fs_thumbnail.height = 0;
      fs_thumbnail.is_valid = false;
      fs_thumbnail.path[0] = '\0';

      mini_thumbnail.width = 0;
      mini_thumbnail.height = 0;
      mini_thumbnail.is_valid = false;
      mini_thumbnail.path[0] = '\0';

      mini_left_thumbnail.width = 0;
      mini_left_thumbnail.height = 0;
      mini_left_thumbnail.is_valid = false;
      mini_left_thumbnail.path[0] = '\0';

      /* Only load thumbnails if currently viewing a
       * playlist (note that thumbnails are loaded
       * immediately, for an optimal user experience) */
      if (rgui->is_playlist)
         rgui_scan_selected_entry_thumbnail(rgui, true);
   }
}