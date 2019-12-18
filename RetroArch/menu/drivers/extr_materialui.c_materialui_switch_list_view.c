#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ menu_materialui_thumbnail_view_portrait; scalar_t__ menu_materialui_thumbnail_view_landscape; } ;
struct TYPE_11__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_12__ {int secondary_thumbnail_enabled; scalar_t__ list_view_type; int need_compute; scalar_t__ is_portrait; int /*<<< orphan*/  primary_thumbnail_available; } ;
typedef  TYPE_3__ materialui_handle_t ;

/* Variables and functions */
 scalar_t__ MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_LAST ; 
 scalar_t__ MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_LAST ; 
 scalar_t__ MUI_LIST_VIEW_DEFAULT ; 
 scalar_t__ MUI_LIST_VIEW_PLAYLIST ; 
 int /*<<< orphan*/  MUI_ONSCREEN_ENTRY_CENTRE ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  materialui_auto_select_onscreen_entry (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  materialui_init_transition_animation (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  materialui_reset_thumbnails () ; 
 int /*<<< orphan*/  materialui_update_list_view (TYPE_3__*) ; 
 size_t menu_navigation_get_selection () ; 

__attribute__((used)) static void materialui_switch_list_view(materialui_handle_t *mui)
{
   settings_t *settings                  = config_get_ptr();
   size_t selection                      = menu_navigation_get_selection();
   bool secondary_thumbnail_enabled_prev = mui->secondary_thumbnail_enabled;

   if (!settings)
      return;

   /* Only enable view switching if we are currently viewing
    * a playlist with thumbnails enabled */
   if ((mui->list_view_type == MUI_LIST_VIEW_DEFAULT) ||
       !mui->primary_thumbnail_available)
      return;

   /* If currently selected item is off screen, then
    * changing the view mode will throw the user to
    * an unexpected off screen location...
    * To prevent this, must immediately select the
    * 'middle' on screen entry */
   materialui_auto_select_onscreen_entry(mui, MUI_ONSCREEN_ENTRY_CENTRE);

   /* Update setting based upon current display orientation */
   if (mui->is_portrait)
   {
      settings->uints.menu_materialui_thumbnail_view_portrait++;

      if (settings->uints.menu_materialui_thumbnail_view_portrait >=
            MATERIALUI_THUMBNAIL_VIEW_PORTRAIT_LAST)
         settings->uints.menu_materialui_thumbnail_view_portrait = 0;
   }
   else
   {
      settings->uints.menu_materialui_thumbnail_view_landscape++;

      if (settings->uints.menu_materialui_thumbnail_view_landscape >=
            MATERIALUI_THUMBNAIL_VIEW_LANDSCAPE_LAST)
         settings->uints.menu_materialui_thumbnail_view_landscape = 0;
   }

   /* Update list view parameters */
   materialui_update_list_view(mui);

   /* If the new list view does not have thumbnails
    * enabled, or last view had dual thumbnails and
    * current does not, reset all existing thumbnails
    * (this would happen automatically at the next
    * menu level change - or destroy context, etc.
    * - but it's cleanest to do it here) */
   if ((mui->list_view_type == MUI_LIST_VIEW_DEFAULT) ||
       (mui->list_view_type == MUI_LIST_VIEW_PLAYLIST) ||
       (secondary_thumbnail_enabled_prev && !mui->secondary_thumbnail_enabled))
      materialui_reset_thumbnails();

   /* We want to 'fade in' when switching views, so
    * trigger normal transition animation */
   materialui_init_transition_animation(mui, settings);

   mui->need_compute = true;
}