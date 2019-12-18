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
typedef  int /*<<< orphan*/  settings_t ;
struct TYPE_3__ {unsigned int landscape_entry_margin; int last_landscape_layout_optimization; scalar_t__ last_height; scalar_t__ nav_bar_layout_width; scalar_t__ last_width; int /*<<< orphan*/  list_view_type; scalar_t__ is_portrait; } ;
typedef  TYPE_1__ materialui_handle_t ;

/* Variables and functions */
#define  MATERIALUI_LANDSCAPE_LAYOUT_OPTIMIZATION_ALWAYS 136 
#define  MATERIALUI_LANDSCAPE_LAYOUT_OPTIMIZATION_DISABLED 135 
#define  MATERIALUI_LANDSCAPE_LAYOUT_OPTIMIZATION_EXCLUDE_THUMBNAIL_VIEWS 134 
#define  MUI_LIST_VIEW_DEFAULT 133 
#define  MUI_LIST_VIEW_PLAYLIST 132 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON 131 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE 130 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM 129 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL 128 

__attribute__((used)) static void materialui_set_landscape_optimisations_enable(
      materialui_handle_t *mui, settings_t *settings)
{
   bool optimize_landscape_layout = false;

   /* In landscape orientations, menu lists are too wide
    * (to the extent that they are rather uncomfortable
    * to look at...)
    * > Depending upon user configuration, we therefore
    *   use additional padding at the left/right sides of
    *   the screen */

   /* Disable optimisations by default */
   mui->landscape_entry_margin = 0;

   /* Early out if current orientation is portrait */
   if (mui->is_portrait)
      return;

   /* Check whether optimisations are enabled, globally
    * or for current list view type */
   switch (mui->last_landscape_layout_optimization)
   {
      case MATERIALUI_LANDSCAPE_LAYOUT_OPTIMIZATION_ALWAYS:
         optimize_landscape_layout = true;
         break;
      case MATERIALUI_LANDSCAPE_LAYOUT_OPTIMIZATION_EXCLUDE_THUMBNAIL_VIEWS:

         switch (mui->list_view_type)
         {
            case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL:
            case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM:
            case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE:
            case MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON:
               optimize_landscape_layout = false;
               break;
            case MUI_LIST_VIEW_PLAYLIST:
            case MUI_LIST_VIEW_DEFAULT:
            default:
               optimize_landscape_layout = true;
               break;
         }

         break;

      case MATERIALUI_LANDSCAPE_LAYOUT_OPTIMIZATION_DISABLED:
      default:
         optimize_landscape_layout = false;
         break;
   }

   /* Calculate landscape entry margin size, if required */
   if (optimize_landscape_layout)
   {
      /* After testing various approaches, it seems that
       * simply enforcing a 4:3 aspect ratio produces the
       * best results */
      const float base_aspect = 4.0f / 3.0f;
      float landscape_margin  =
            ((float)(mui->last_width - mui->nav_bar_layout_width) -
                  (base_aspect * (float)mui->last_height)) / 2.0f;

      /* Note: Want to round down here */
      if (landscape_margin > 1.0f)
         mui->landscape_entry_margin = (unsigned)landscape_margin;
   }
}