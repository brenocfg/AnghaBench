#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** badge_id_list; int /*<<< orphan*/ * menu_texture_list; scalar_t__* badge_locked; } ;
typedef  TYPE_1__ badges_ctx_t ;
typedef  int /*<<< orphan*/  badge_file ;

/* Variables and functions */
 int /*<<< orphan*/  APPLICATION_SPECIAL_DIRECTORY_THUMBNAILS_CHEEVOS_BADGES ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  fill_pathname_application_special (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_reset_textures_list (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

void set_badge_menu_texture(badges_ctx_t * badges, int i)
{
   char badge_file[16];
   char fullpath[PATH_MAX_LENGTH];

   snprintf(badge_file, sizeof(badge_file), "%s%s", badges->badge_id_list[i],
         badges->badge_locked[i] ? "_lock.png" : ".png");

   fill_pathname_application_special(fullpath,
         PATH_MAX_LENGTH * sizeof(char),
         APPLICATION_SPECIAL_DIRECTORY_THUMBNAILS_CHEEVOS_BADGES);

#ifdef HAVE_MENU
   menu_display_reset_textures_list(badge_file, fullpath,
         &badges->menu_texture_list[i],TEXTURE_FILTER_MIPMAP_LINEAR, NULL, NULL);
#endif
}