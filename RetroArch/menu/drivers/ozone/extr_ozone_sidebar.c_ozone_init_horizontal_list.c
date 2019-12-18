#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ menu_content_show_playlists; } ;
struct TYPE_12__ {char* directory_playlist; } ;
struct TYPE_14__ {TYPE_2__ bools; TYPE_1__ paths; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_15__ {int /*<<< orphan*/  horizontal_list; } ;
typedef  TYPE_4__ ozone_handle_t ;
struct TYPE_16__ {void* path; int /*<<< orphan*/  enum_idx; int /*<<< orphan*/  type_default; void* exts; void* label; int /*<<< orphan*/  list; } ;
typedef  TYPE_5__ menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLIST_DATABASE_PLAYLISTS_HORIZONTAL ; 
 int /*<<< orphan*/  FILE_TYPE_PLAIN ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLISTS_TAB ; 
 TYPE_3__* config_get_ptr () ; 
 scalar_t__ menu_displaylist_ctl (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  menu_displaylist_info_free (TYPE_5__*) ; 
 int /*<<< orphan*/  menu_displaylist_info_init (TYPE_5__*) ; 
 int /*<<< orphan*/  menu_displaylist_process (TYPE_5__*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (void*) ; 

void ozone_init_horizontal_list(ozone_handle_t *ozone)
{
   menu_displaylist_info_t info;
   settings_t *settings         = config_get_ptr();

   menu_displaylist_info_init(&info);

   info.list                    = ozone->horizontal_list;
   info.path                    = strdup(
         settings->paths.directory_playlist);
   info.label                   = strdup(
         msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB));
   info.exts                    = strdup("lpl");
   info.type_default            = FILE_TYPE_PLAIN;
   info.enum_idx                = MENU_ENUM_LABEL_PLAYLISTS_TAB;

   if (settings->bools.menu_content_show_playlists && !string_is_empty(info.path))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_DATABASE_PLAYLISTS_HORIZONTAL, &info))
         menu_displaylist_process(&info);
   }

   menu_displaylist_info_free(&info);
}