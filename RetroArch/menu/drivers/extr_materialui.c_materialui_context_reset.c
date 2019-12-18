#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  path_menu_wallpaper; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  materialui_handle_t ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  materialui_context_bg_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  materialui_context_reset_textures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  materialui_layout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_display_allocate_white_texture () ; 
 int /*<<< orphan*/  menu_display_handle_wallpaper_upload ; 
 scalar_t__ path_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_push_image_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_monitor_reset () ; 
 int /*<<< orphan*/  video_driver_supports_rgba () ; 

__attribute__((used)) static void materialui_context_reset(void *data, bool is_threaded)
{
   materialui_handle_t *mui = (materialui_handle_t*)data;
   settings_t *settings     = config_get_ptr();

   if (!mui || !settings)
      return;

   materialui_layout(mui, is_threaded);
   materialui_context_bg_destroy(mui);
   menu_display_allocate_white_texture();
   materialui_context_reset_textures(mui);

   if (path_is_valid(settings->paths.path_menu_wallpaper))
      task_push_image_load(settings->paths.path_menu_wallpaper,
            video_driver_supports_rgba(), 0,
            menu_display_handle_wallpaper_upload, NULL);

   video_driver_monitor_reset();
}