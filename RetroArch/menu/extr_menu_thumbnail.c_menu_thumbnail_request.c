#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ network_on_demand_thumbnails; } ;
struct TYPE_10__ {int /*<<< orphan*/  menu_thumbnail_upscale_threshold; } ;
struct TYPE_12__ {TYPE_2__ bools; TYPE_1__ uints; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_13__ {int /*<<< orphan*/  list_id; TYPE_5__* thumbnail; } ;
typedef  TYPE_4__ menu_thumbnail_tag_t ;
struct TYPE_14__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_5__ menu_thumbnail_t ;
typedef  int /*<<< orphan*/  menu_thumbnail_path_data_t ;
typedef  int /*<<< orphan*/  last_img_name ;
typedef  enum menu_thumbnail_id { ____Placeholder_menu_thumbnail_id } menu_thumbnail_id ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_THUMBNAIL_STATUS_MISSING ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_STATUS_PENDING ; 
 int PATH_MAX_LENGTH ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_thumbnail_get_img_name (int /*<<< orphan*/ *,char const**) ; 
 int menu_thumbnail_get_path (int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_get_system (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_handle_upload ; 
 scalar_t__ menu_thumbnail_is_enabled (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_thumbnail_list_id ; 
 int /*<<< orphan*/  menu_thumbnail_reset (TYPE_5__*) ; 
 scalar_t__ menu_thumbnail_update_path (int /*<<< orphan*/ *,int) ; 
 scalar_t__ path_is_valid (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ task_push_image_load (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  task_push_pl_entry_thumbnail_download (char const*,int /*<<< orphan*/ *,unsigned int,int,int) ; 
 int /*<<< orphan*/  video_driver_supports_rgba () ; 

void menu_thumbnail_request(
      menu_thumbnail_path_data_t *path_data, enum menu_thumbnail_id thumbnail_id,
      playlist_t *playlist, size_t idx, menu_thumbnail_t *thumbnail)
{
   settings_t *settings                = config_get_ptr();
   const char *thumbnail_path          = NULL;
   bool has_thumbnail                  = false;

   if (!path_data || !thumbnail || !settings)
      return;

   /* Reset thumbnail, then set 'missing' status by default
    * (saves a number of checks later) */
   menu_thumbnail_reset(thumbnail);
   thumbnail->status = MENU_THUMBNAIL_STATUS_MISSING;

   /* Update/extract thumbnail path */
   if (menu_thumbnail_is_enabled(path_data, thumbnail_id))
      if (menu_thumbnail_update_path(path_data, thumbnail_id))
         has_thumbnail = menu_thumbnail_get_path(path_data, thumbnail_id, &thumbnail_path);

   /* Load thumbnail, if required */
   if (has_thumbnail)
   {
      if (path_is_valid(thumbnail_path))
      {
         menu_thumbnail_tag_t *thumbnail_tag =
               (menu_thumbnail_tag_t*)calloc(1, sizeof(menu_thumbnail_tag_t));

         if (!thumbnail_tag)
            return;

         /* Configure user data */
         thumbnail_tag->thumbnail = thumbnail;
         thumbnail_tag->list_id   = menu_thumbnail_list_id;

         /* Would like to cancel any existing image load tasks
          * here, but can't see how to do it... */
         if(task_push_image_load(
               thumbnail_path, video_driver_supports_rgba(),
               settings->uints.menu_thumbnail_upscale_threshold,
               menu_thumbnail_handle_upload, thumbnail_tag))
            thumbnail->status = MENU_THUMBNAIL_STATUS_PENDING;
      }
#ifdef HAVE_NETWORKING
      /* Handle on demand thumbnail downloads */
      else if (settings->bools.network_on_demand_thumbnails)
      {
         const char *system                         = NULL;
         const char *img_name                       = NULL;
         static char last_img_name[PATH_MAX_LENGTH] = {0};

         if (!playlist)
            return;

         /* Get current image name */
         if (!menu_thumbnail_get_img_name(path_data, &img_name))
            return;

         /* Only trigger a thumbnail download if image
          * name has changed since the last call of
          * menu_thumbnail_request()
          * > Allows menu_thumbnail_request() to be used
          *   for successive right/left thumbnail requests
          *   with minimal duplication of effort
          *   (i.e. task_push_pl_entry_thumbnail_download()
          *   will automatically cancel if a download for the
          *   existing playlist entry is pending, but the
          *   checks required for this involve significant
          *   overheads. We can avoid this entirely with
          *   a simple string comparison) */
         if (string_is_equal(img_name, last_img_name))
            return;

         strlcpy(last_img_name, img_name, sizeof(last_img_name));

         /* Get system name */
         if (!menu_thumbnail_get_system(path_data, &system))
            return;

         /* Trigger thumbnail download */
         task_push_pl_entry_thumbnail_download(
               system, playlist, (unsigned)idx,
               false, true);
      }
#endif
   }
}