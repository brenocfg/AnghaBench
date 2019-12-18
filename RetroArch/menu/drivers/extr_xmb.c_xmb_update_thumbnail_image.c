#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  thumbnail_path_data; int /*<<< orphan*/  left_thumbnail; int /*<<< orphan*/  thumbnail; } ;
typedef  TYPE_3__ xmb_handle_t ;
struct TYPE_7__ {scalar_t__ network_on_demand_thumbnails; } ;
struct TYPE_6__ {int /*<<< orphan*/  menu_thumbnail_upscale_threshold; } ;
struct TYPE_9__ {TYPE_2__ bools; TYPE_1__ uints; } ;
typedef  TYPE_4__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_THUMBNAIL_LEFT ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_RIGHT ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_display_handle_left_thumbnail_upload ; 
 int /*<<< orphan*/  menu_display_handle_thumbnail_upload ; 
 scalar_t__ menu_navigation_get_selection () ; 
 scalar_t__ menu_thumbnail_get_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ menu_thumbnail_get_system (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ path_is_valid (char const*) ; 
 int /*<<< orphan*/  playlist_get_cached () ; 
 int /*<<< orphan*/  task_push_image_load (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_push_pl_entry_thumbnail_download (char const*,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int video_driver_supports_rgba () ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xmb_update_thumbnail_image(void *data)
{
   settings_t *settings             = config_get_ptr();
   xmb_handle_t *xmb                = (xmb_handle_t*)data;
   const char *right_thumbnail_path = NULL;
   const char *left_thumbnail_path  = NULL;
   bool supports_rgba               = video_driver_supports_rgba();

   /* Have to wrap `thumbnails_missing` like this to silence
    * brain dead `set but not used` warnings when networking
    * is disabled... */
#ifdef HAVE_NETWORKING
   bool thumbnails_missing          = false;
#endif

   if (!xmb || !settings)
      return;

   if (menu_thumbnail_get_path(xmb->thumbnail_path_data, MENU_THUMBNAIL_RIGHT, &right_thumbnail_path))
   {
      if (path_is_valid(right_thumbnail_path))
         task_push_image_load(right_thumbnail_path,
               supports_rgba, settings->uints.menu_thumbnail_upscale_threshold,
               menu_display_handle_thumbnail_upload, NULL);
      else
      {
         video_driver_texture_unload(&xmb->thumbnail);
#ifdef HAVE_NETWORKING
         thumbnails_missing = true;
#endif
      }
   }
   else
      video_driver_texture_unload(&xmb->thumbnail);

   if (menu_thumbnail_get_path(xmb->thumbnail_path_data, MENU_THUMBNAIL_LEFT, &left_thumbnail_path))
   {
      if (path_is_valid(left_thumbnail_path))
         task_push_image_load(left_thumbnail_path,
               supports_rgba, settings->uints.menu_thumbnail_upscale_threshold,
               menu_display_handle_left_thumbnail_upload, NULL);
      else
      {
         video_driver_texture_unload(&xmb->left_thumbnail);
#ifdef HAVE_NETWORKING
         thumbnails_missing = true;
#endif
      }
   }
   else
      video_driver_texture_unload(&xmb->left_thumbnail);

#ifdef HAVE_NETWORKING
   /* On demand thumbnail downloads */
   if (thumbnails_missing)
   {
      if (settings->bools.network_on_demand_thumbnails)
      {
         const char *system = NULL;

         if (menu_thumbnail_get_system(xmb->thumbnail_path_data, &system))
            task_push_pl_entry_thumbnail_download(system,
                  playlist_get_cached(), (unsigned)menu_navigation_get_selection(),
                  false, true);
      }
   }
#endif
}