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
struct TYPE_6__ {int menu_materialui_thumbnail_view_portrait; int menu_materialui_thumbnail_view_landscape; } ;
struct TYPE_7__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {int primary_thumbnail_available; void* list_view_type; scalar_t__ is_portrait; int /*<<< orphan*/  thumbnail_path_data; int /*<<< orphan*/  is_playlist; } ;
typedef  TYPE_3__ materialui_handle_t ;

/* Variables and functions */
#define  MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_DISABLED 135 
#define  MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_LIST_LARGE 134 
#define  MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_LIST_MEDIUM 133 
#define  MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_LIST_SMALL 132 
#define  MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_DISABLED 131 
#define  MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_DUAL_ICON 130 
#define  MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_LIST_MEDIUM 129 
#define  MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_LIST_SMALL 128 
 int /*<<< orphan*/  MENU_THUMBNAIL_RIGHT ; 
 void* MUI_LIST_VIEW_DEFAULT ; 
 void* MUI_LIST_VIEW_PLAYLIST ; 
 void* MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON ; 
 void* MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE ; 
 void* MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM ; 
 void* MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL ; 
 int menu_thumbnail_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void materialui_set_list_view_type(
      materialui_handle_t *mui, settings_t *settings)
{
   if (!mui->is_playlist)
   {
      /* This is not a playlist - set default list
       * view and register that primary thumbnail
       * is disabled */
      mui->list_view_type              = MUI_LIST_VIEW_DEFAULT;
      mui->primary_thumbnail_available = false;
   }
   else
   {
      /* This is a playlist - set non-thumbnail view
       * by default (saves checks later) */
      mui->list_view_type = MUI_LIST_VIEW_PLAYLIST;

      /* Check whether primary thumbnail is enabled */
      mui->primary_thumbnail_available =
            menu_thumbnail_is_enabled(mui->thumbnail_path_data, MENU_THUMBNAIL_RIGHT);

      if (mui->primary_thumbnail_available)
      {
         /* Get thumbnail view mode based on current
          * display orientation */
         if (mui->is_portrait)
         {
            switch (settings->uints.menu_materialui_thumbnail_view_portrait)
            {
               case MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_LIST_SMALL:
                  mui->list_view_type = MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL;
                  break;
               case MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_LIST_MEDIUM:
                  mui->list_view_type = MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM;
                  break;
               case MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_DUAL_ICON:
                  mui->list_view_type = MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON;
                  break;
               case MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_DISABLED:
               default:
                  mui->list_view_type = MUI_LIST_VIEW_PLAYLIST;
                  break;
            }
         }
         else
         {
            switch (settings->uints.menu_materialui_thumbnail_view_landscape)
            {
               case MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_LIST_SMALL:
                  mui->list_view_type = MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL;
                  break;
               case MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_LIST_MEDIUM:
                  mui->list_view_type = MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM;
                  break;
               case MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_LIST_LARGE:
                  mui->list_view_type = MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE;
                  break;
               case MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_DISABLED:
               default:
                  mui->list_view_type = MUI_LIST_VIEW_PLAYLIST;
                  break;
            }
         }
      }
   }
}