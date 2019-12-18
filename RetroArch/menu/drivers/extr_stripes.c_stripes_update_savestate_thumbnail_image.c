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
struct TYPE_2__ {int /*<<< orphan*/  savestate_thumbnail; int /*<<< orphan*/  savestate_thumbnail_file_path; } ;
typedef  TYPE_1__ stripes_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_handle_savestate_thumbnail_upload ; 
 scalar_t__ path_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_push_image_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_supports_rgba () ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stripes_update_savestate_thumbnail_image(void *data)
{
   stripes_handle_t *stripes = (stripes_handle_t*)data;
   if (!stripes)
      return;

   if (path_is_valid(stripes->savestate_thumbnail_file_path))
      task_push_image_load(stripes->savestate_thumbnail_file_path,
            video_driver_supports_rgba(), 0,
            menu_display_handle_savestate_thumbnail_upload, NULL);
   else
      video_driver_texture_unload(&stripes->savestate_thumbnail);
}