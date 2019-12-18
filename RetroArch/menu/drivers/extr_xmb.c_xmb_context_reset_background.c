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
struct TYPE_4__ {char* path_menu_wallpaper; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  menu_display_handle_wallpaper_upload ; 
 scalar_t__ path_is_valid (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  task_push_image_load (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_supports_rgba () ; 

__attribute__((used)) static void xmb_context_reset_background(const char *iconpath)
{
   char *path                  = NULL;
   settings_t *settings        = config_get_ptr();
   const char *path_menu_wp    = settings->paths.path_menu_wallpaper;

   if (!string_is_empty(path_menu_wp))
      path = strdup(path_menu_wp);
   else if (!string_is_empty(iconpath))
   {
      path    = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
      path[0] = '\0';

      fill_pathname_join(path, iconpath, "bg.png",
            PATH_MAX_LENGTH * sizeof(char));
   }

   if (path_is_valid(path))
      task_push_image_load(path,
            video_driver_supports_rgba(), 0,
            menu_display_handle_wallpaper_upload, NULL);

#ifdef ORBIS
   /* To avoid weird behaviour on orbis with remote host */
   RARCH_LOG("[XMB] after task\n");
   sleep(5);
#endif
   if (path)
      free(path);
}