#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * left_thumbnail_file_path; int /*<<< orphan*/  left_thumbnail; int /*<<< orphan*/ * thumbnail_file_path; int /*<<< orphan*/  thumbnail; } ;
typedef  TYPE_1__ stripes_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_handle_left_thumbnail_upload ; 
 int /*<<< orphan*/  menu_display_handle_thumbnail_upload ; 
 scalar_t__ path_is_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_push_image_load (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int video_driver_supports_rgba () ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stripes_update_thumbnail_image(void *data)
{
   stripes_handle_t *stripes = (stripes_handle_t*)data;
   bool supports_rgba        = video_driver_supports_rgba();
   if (!stripes)
      return;

   if (!(string_is_empty(stripes->thumbnail_file_path)))
      {
         if (path_is_valid(stripes->thumbnail_file_path))
            task_push_image_load(stripes->thumbnail_file_path,
                  supports_rgba, 0,
                  menu_display_handle_thumbnail_upload, NULL);
         else
            video_driver_texture_unload(&stripes->thumbnail);

         free(stripes->thumbnail_file_path);
         stripes->thumbnail_file_path = NULL;
      }

   if (!(string_is_empty(stripes->left_thumbnail_file_path)))
      {
         if (path_is_valid(stripes->left_thumbnail_file_path))
            task_push_image_load(stripes->left_thumbnail_file_path,
                  supports_rgba, 0,
                  menu_display_handle_left_thumbnail_upload, NULL);
         else
            video_driver_texture_unload(&stripes->left_thumbnail);

         free(stripes->left_thumbnail_file_path);
         stripes->left_thumbnail_file_path = NULL;
      }
}