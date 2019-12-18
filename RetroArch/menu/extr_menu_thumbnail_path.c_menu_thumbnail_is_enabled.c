#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  menu_left_thumbnails; int /*<<< orphan*/  menu_thumbnails; } ;
struct TYPE_7__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {int /*<<< orphan*/  playlist_left_mode; int /*<<< orphan*/  playlist_right_mode; } ;
typedef  TYPE_3__ menu_thumbnail_path_data_t ;
typedef  enum menu_thumbnail_id { ____Placeholder_menu_thumbnail_id } menu_thumbnail_id ;

/* Variables and functions */
#define  MENU_THUMBNAIL_LEFT 129 
#define  MENU_THUMBNAIL_RIGHT 128 
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_MODE_DEFAULT ; 
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_MODE_OFF ; 
 TYPE_2__* config_get_ptr () ; 

bool menu_thumbnail_is_enabled(menu_thumbnail_path_data_t *path_data, enum menu_thumbnail_id thumbnail_id)
{
   settings_t *settings = config_get_ptr();
   
   if (!path_data || !settings)
      return false;
   
   switch (thumbnail_id)
   {
      case MENU_THUMBNAIL_RIGHT:
         if (path_data->playlist_right_mode != PLAYLIST_THUMBNAIL_MODE_DEFAULT)
            return path_data->playlist_right_mode != PLAYLIST_THUMBNAIL_MODE_OFF;
         return settings->uints.menu_thumbnails != 0;
      case MENU_THUMBNAIL_LEFT:
         if (path_data->playlist_left_mode != PLAYLIST_THUMBNAIL_MODE_DEFAULT)
            return path_data->playlist_left_mode != PLAYLIST_THUMBNAIL_MODE_OFF;
         return settings->uints.menu_left_thumbnails != 0;
      default:
         break;
   }
   
   return false;
}