#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ menu_rgui_aspect_ratio_lock; } ;
struct TYPE_10__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ rgui_video_settings_t ;
struct TYPE_12__ {int is_playlist; int thumbnail_load_pending; int ignore_resize_events; int /*<<< orphan*/  content_video_settings; int /*<<< orphan*/  menu_video_settings; int /*<<< orphan*/  menu_title; } ;
typedef  TYPE_4__ rgui_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_FAVORITES_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_PLAYLIST_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_VIDEO_SETTINGS_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_LOAD_CONTENT_HISTORY ; 
 scalar_t__ RGUI_ASPECT_RATIO_LOCK_NONE ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_entries_get_title (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgui_get_video_config (TYPE_3__*) ; 
 scalar_t__ rgui_is_video_config_equal (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rgui_navigation_set (void*,int) ; 
 int /*<<< orphan*/  rgui_set_video_config (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rgui_populate_entries(void *data,
      const char *path,
      const char *label, unsigned k)
{
   rgui_t *rgui         = (rgui_t*)data;
   settings_t *settings = config_get_ptr();
   
   if (!rgui || !settings)
      return;
   
   /* Check whether we are currently viewing a playlist */
   rgui->is_playlist = string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_PLAYLIST_LIST)) ||
                       string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_LOAD_CONTENT_HISTORY)) ||
                       string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_FAVORITES_LIST));
   
   /* Set menu title */
   menu_entries_get_title(rgui->menu_title, sizeof(rgui->menu_title));
   
   /* Cancel any pending thumbnail load operations */
   rgui->thumbnail_load_pending = false;
   
   rgui_navigation_set(data, true);
   
   /* If aspect ratio lock is enabled, must restore
    * content video settings when accessing the video
    * settings menu... */
   if (settings->uints.menu_rgui_aspect_ratio_lock != RGUI_ASPECT_RATIO_LOCK_NONE)
   {
      if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_VIDEO_SETTINGS_LIST)))
      {
         /* Make sure that any changes made while accessing
          * the video settings menu are preserved */
         rgui_video_settings_t current_video_settings = {0};
         rgui_get_video_config(&current_video_settings);
         if (rgui_is_video_config_equal(&current_video_settings, &rgui->menu_video_settings))
         {
            rgui_set_video_config(rgui, &rgui->content_video_settings, false);
            /* Menu viewport has been overridden - must ignore
             * resize events until the menu is next toggled off */
            rgui->ignore_resize_events = true;
         }
      }
   }
}