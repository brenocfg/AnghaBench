#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int font_height; } ;
struct TYPE_6__ {int /*<<< orphan*/  font_height; } ;
struct TYPE_8__ {TYPE_2__ hint; TYPE_1__ list; } ;
struct TYPE_9__ {int list_view_type; int thumbnail_height_max; int icon_size; unsigned int thumbnail_width_max; int dip_base_unit_size; int margin; int landscape_entry_margin; scalar_t__ nav_bar_layout_width; scalar_t__ last_width; TYPE_3__ font_data; } ;
typedef  TYPE_4__ materialui_handle_t ;

/* Variables and functions */
#define  MUI_LIST_VIEW_DEFAULT 133 
#define  MUI_LIST_VIEW_PLAYLIST 132 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON 131 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE 130 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM 129 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL 128 
 float MUI_THUMBNAIL_DEFAULT_ASPECT_RATIO ; 

__attribute__((used)) static void materialui_set_thumbnail_dimensions(materialui_handle_t *mui)
{
   switch (mui->list_view_type)
   {
      case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL:

         /* Maximum height is just standard icon size */
         mui->thumbnail_height_max = mui->icon_size;

         /* Set thumbnail width based on max height */
         mui->thumbnail_width_max =
               (unsigned)(((float)mui->thumbnail_height_max *
                     MUI_THUMBNAIL_DEFAULT_ASPECT_RATIO) + 0.5f);

         break;

      case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM:

         /* Maximum height corresponds to text height when
          * showing full playlist sublabel metadata
          * (core association + runtime info)
          * > One line of list text + three lines of
          *   hint text + padding */
         mui->thumbnail_height_max =
               mui->font_data.list.font_height +
               (3 * mui->font_data.hint.font_height) +
               (mui->dip_base_unit_size / 10);

         /* Set thumbnail width based on max height
          * Note: We're duplicating this calculation each time
          * for consistency - some view modes will require
          * something different, and we want each case to
          * be self-contained */
         mui->thumbnail_width_max =
               (unsigned)(((float)mui->thumbnail_height_max *
                     MUI_THUMBNAIL_DEFAULT_ASPECT_RATIO) + 0.5f);

         break;

      case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE:

         /* Maximum height corresponds to twice the
          * text height when showing full playlist sublabel
          * metadata (core association + runtime info)
          * > Two lines of list text + three lines of
          *   hint text (no padding) */
         mui->thumbnail_height_max =
               (mui->font_data.list.font_height +
                (3 * mui->font_data.hint.font_height)) * 2;

         /* Set thumbnail width based on max height */
         mui->thumbnail_width_max =
               (unsigned)(((float)mui->thumbnail_height_max *
                     MUI_THUMBNAIL_DEFAULT_ASPECT_RATIO) + 0.5f);

         break;

      case MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON:
         {
            /* This view shows two thumbnail icons
             * side-by-side across the full width of
             * the list area */

            /* > Get total usable width
             *   (list view width minus padding between
             *   and either side of thumbnails) */
            int usable_width =
                  (int)mui->last_width - (int)(mui->margin * 3) -
                  (int)(mui->landscape_entry_margin * 2) - (int)mui->nav_bar_layout_width;

            /* > Sanity check */
            if (usable_width < 2)
            {
               mui->thumbnail_width_max  = 0;
               mui->thumbnail_height_max = 0;
            }

            /* > Get maximum thumbnail width */
            mui->thumbnail_width_max = (usable_width >> 1);

            /* > Set thumbnail height based on max width */
            mui->thumbnail_height_max =
                  (unsigned)(((float)mui->thumbnail_width_max *
                        (1.0f / MUI_THUMBNAIL_DEFAULT_ASPECT_RATIO)) + 0.5f);                  
         }
         break;

      case MUI_LIST_VIEW_PLAYLIST:
      case MUI_LIST_VIEW_DEFAULT:
      default:
         /* Not required, but might as well zero
          * out thumbnail dimensions... */
         mui->thumbnail_height_max = 0;
         mui->thumbnail_width_max  = 0;
         break;
   }
}