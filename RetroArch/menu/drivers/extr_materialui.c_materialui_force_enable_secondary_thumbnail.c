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
struct TYPE_6__ {scalar_t__ menu_left_thumbnails; scalar_t__ menu_thumbnails; } ;
struct TYPE_7__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {int /*<<< orphan*/  thumbnail_path_data; } ;
typedef  TYPE_3__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_THUMBNAIL_LEFT ; 
 scalar_t__ MUI_DEFAULT_SECONDARY_THUMBNAIL_FALLBACK_TYPE ; 
 scalar_t__ MUI_DEFAULT_SECONDARY_THUMBNAIL_TYPE ; 
 int menu_thumbnail_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool materialui_force_enable_secondary_thumbnail(
      materialui_handle_t *mui, settings_t *settings)
{
   /* If secondary thumbnail is already enabled,
    * do nothing */
   if (menu_thumbnail_is_enabled(
         mui->thumbnail_path_data, MENU_THUMBNAIL_LEFT))
      return true;

   /* Secondary thumbnail is disabled
    * > Check if this is a global setting... */
   if (settings->uints.menu_left_thumbnails == 0)
   {
      /* > If possible, set secondary thumbnail
       *   type to MUI_DEFAULT_SECONDARY_THUMBNAIL_TYPE
       * > If primary thumbnail is already set to
       *   MUI_DEFAULT_SECONDARY_THUMBNAIL_TYPE, use
       *   MUI_DEFAULT_SECONDARY_THUMBNAIL_FALLBACK_TYPE
       *   instead */
      if (settings->uints.menu_thumbnails ==
            MUI_DEFAULT_SECONDARY_THUMBNAIL_TYPE)
         settings->uints.menu_left_thumbnails =
               MUI_DEFAULT_SECONDARY_THUMBNAIL_FALLBACK_TYPE;
      else
         settings->uints.menu_left_thumbnails =
               MUI_DEFAULT_SECONDARY_THUMBNAIL_TYPE;
   }

   /* Final check - this will return true unless a
    * per-playlist override is in place */
   return menu_thumbnail_is_enabled(
         mui->thumbnail_path_data, MENU_THUMBNAIL_LEFT);
}