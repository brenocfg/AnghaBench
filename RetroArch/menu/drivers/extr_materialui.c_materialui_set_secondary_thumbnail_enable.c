#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  menu_materialui_dual_thumbnail_list_view_enable; } ;
struct TYPE_11__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_10__ {scalar_t__ width; } ;
struct TYPE_12__ {int list_view_type; int secondary_thumbnail_enabled; int margin; int landscape_entry_margin; int thumbnail_width_max; TYPE_2__ scrollbar; int /*<<< orphan*/  is_portrait; scalar_t__ nav_bar_layout_width; scalar_t__ last_width; } ;
typedef  TYPE_4__ materialui_handle_t ;

/* Variables and functions */
#define  MUI_LIST_VIEW_DEFAULT 133 
#define  MUI_LIST_VIEW_PLAYLIST 132 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON 131 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE 130 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM 129 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL 128 
 int /*<<< orphan*/  materialui_force_enable_secondary_thumbnail (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static void materialui_set_secondary_thumbnail_enable(
      materialui_handle_t *mui, settings_t *settings)
{
   switch (mui->list_view_type)
   {
      case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL:
      case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM:
      case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE:
         /* List view has optional secondary thumbnails */
         {
            int usable_width     = 0;
            int thumbnail_margin = 0;

            /* Disable by default */
            mui->secondary_thumbnail_enabled = false;

            /* Check whether user has manually disabled
             * secondary thumbnails */
            if (!settings->bools.menu_materialui_dual_thumbnail_list_view_enable)
               return;

            /* Attempt to force enable secondary thumbnails if
             * global 'Secondary Thumbnail' type is set to OFF */
            if (!materialui_force_enable_secondary_thumbnail(mui, settings))
               return;

            /* Secondary thumbnails are supported/enabled
             * Check whether screen has sufficient
             * width to display them */

            /* > Get total usable width */
            usable_width =
                  (int)mui->last_width - (int)(mui->margin * 2) -
                  (int)(mui->landscape_entry_margin * 2) - (int)mui->nav_bar_layout_width;

            /* > Account for additional padding (margins) when
             *   using portrait orientations */
            if (mui->is_portrait)
               thumbnail_margin = (int)mui->scrollbar.width;
            /* > Account for additional padding (margins) when
             *   using landscape orientations */
            else
               if (mui->landscape_entry_margin < mui->margin)
                  thumbnail_margin = (int)(mui->margin - mui->landscape_entry_margin);

            /* > Get remaining (text) width after drawing
             *   primary + secondary thumbnails */
            usable_width -= 2 * ((int)mui->thumbnail_width_max + thumbnail_margin);

            /* > A secondary thumbnail may only be drawn
             *   if the remaining (text) width is greater
             *   than twice the thumbnail width */
            mui->secondary_thumbnail_enabled =
                  usable_width > (int)(mui->thumbnail_width_max * 2);
         }
         break;
      case MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON:
         /* List view requires secondary thumbnails
          * > Attempt to force enable, but set
          *   mui->secondary_thumbnail_enabled to 'true'
          *   regardless of the result since we still
          *   want 'missing thumbnail' images if
          *   thumbnails are actively disabled via
          *   a per-playlist override */
         materialui_force_enable_secondary_thumbnail(mui, settings);
         mui->secondary_thumbnail_enabled = true;
         break;
      case MUI_LIST_VIEW_PLAYLIST:
      case MUI_LIST_VIEW_DEFAULT:
      default:
         /* List view has no thumbnails */
         mui->secondary_thumbnail_enabled = false;
         break;
   }
}