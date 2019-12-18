#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;
typedef  int /*<<< orphan*/  menu_entry_t ;
struct TYPE_9__ {int dragged; } ;
struct TYPE_10__ {unsigned int nav_bar_layout_width; int icon_size; unsigned int landscape_entry_margin; int /*<<< orphan*/  is_dropdown_list; int /*<<< orphan*/  is_file_list; int /*<<< orphan*/  is_playlist; int /*<<< orphan*/  primary_thumbnail_available; int /*<<< orphan*/  nav_bar_layout_height; TYPE_1__ scrollbar; } ;
typedef  TYPE_2__ materialui_handle_t ;
typedef  enum menu_input_pointer_gesture { ____Placeholder_menu_input_pointer_gesture } menu_input_pointer_gesture ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ACTION_CANCEL ; 
 int /*<<< orphan*/  MENU_ACTION_LEFT ; 
 int /*<<< orphan*/  MENU_ACTION_RIGHT ; 
 int /*<<< orphan*/  MENU_ACTION_SELECT ; 
 int /*<<< orphan*/  MENU_ACTION_START ; 
#define  MENU_INPUT_GESTURE_LONG_PRESS 132 
#define  MENU_INPUT_GESTURE_SHORT_PRESS 131 
#define  MENU_INPUT_GESTURE_SWIPE_LEFT 130 
#define  MENU_INPUT_GESTURE_SWIPE_RIGHT 129 
#define  MENU_INPUT_GESTURE_TAP 128 
 int /*<<< orphan*/  MENU_LIST_PLAIN ; 
 int /*<<< orphan*/  MUI_THUMBNAIL_STREAM_DELAY_DEFAULT ; 
 int materialui_list_get_size (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int materialui_menu_entry_action (TYPE_2__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int materialui_pointer_up_nav_bar (TYPE_2__*,unsigned int,unsigned int,unsigned int,unsigned int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int materialui_pointer_up_swipe_horz_default (TYPE_2__*,int /*<<< orphan*/ *,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 
 int materialui_pointer_up_swipe_horz_plain_list (TYPE_2__*,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,size_t,int) ; 
 int /*<<< orphan*/  materialui_switch_list_view (TYPE_2__*) ; 
 unsigned int menu_display_get_header_height () ; 
 size_t menu_entries_get_size () ; 
 int /*<<< orphan*/  menu_input_dialog_start_search () ; 
 int /*<<< orphan*/  menu_input_set_pointer_y_accel (float) ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  menu_navigation_set_selection (unsigned int) ; 
 int /*<<< orphan*/  menu_thumbnail_set_stream_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static int materialui_pointer_up(void *userdata,
      unsigned x, unsigned y, unsigned ptr,
      enum menu_input_pointer_gesture gesture,
      menu_file_list_cbs_t *cbs,
      menu_entry_t *entry, unsigned action)
{
   unsigned header_height   = menu_display_get_header_height();
   size_t selection         = menu_navigation_get_selection();
   size_t entries_end       = menu_entries_get_size();
   materialui_handle_t *mui = (materialui_handle_t*)userdata;
   unsigned width;
   unsigned height;

   if (!mui)
      return -1;

   /* All input is ignored if user was previously
    * dragging the scrollbar */
   if (mui->scrollbar.dragged)
   {
      /* Must reset scroll acceleration, otherwise
       * list will continue to 'drift' in drag direction */
      menu_input_set_pointer_y_accel(0.0f);

      /* Reset thumbnail stream delay to default */
      menu_thumbnail_set_stream_delay(MUI_THUMBNAIL_STREAM_DELAY_DEFAULT);

      mui->scrollbar.dragged = false;
      return 0;
   }

   video_driver_get_size(&width, &height);

   switch (gesture)
   {
      case MENU_INPUT_GESTURE_TAP:
      case MENU_INPUT_GESTURE_SHORT_PRESS:
         {
            /* Tap/press navigation bar: perform tab-specific action */
            if ((y > height - mui->nav_bar_layout_height) ||
                (x > width  - mui->nav_bar_layout_width))
               return materialui_pointer_up_nav_bar(
                     mui, x, y, width, height, selection, cbs, entry, action);
            /* Tap/press header: Menu back/cancel, or search/switch view */
            else if (y < header_height)
            {
               /* If this is a playlist or file list, enable
                * search functionality */
               if (mui->is_playlist || mui->is_file_list)
               {
                  bool switch_view_enabled  =
                        mui->is_playlist && mui->primary_thumbnail_available;
                  /* Note: We add a little extra padding to minimise
                   * the risk of accidentally triggering a cancel */
                  unsigned back_x_threshold =
                        width -
                        ((switch_view_enabled ? 3 : 2) * mui->icon_size) -
                         mui->nav_bar_layout_width;

                  /* Check if user has touched search icon */
                  if (x > width - mui->icon_size - mui->nav_bar_layout_width)
                     return menu_input_dialog_start_search() ? 0 : -1;
                  /* Check if user has touched switch view icon */
                  else if (switch_view_enabled &&
                           x > width - (2 * mui->icon_size) - mui->nav_bar_layout_width)
                  {
                     materialui_switch_list_view(mui);
                     return 0;
                  }
                  /* Fall back to normal cancel action */
                  else if (x <= back_x_threshold)
                     return materialui_menu_entry_action(mui, entry, selection, MENU_ACTION_CANCEL);
               }
               /* If this is not a playlist or file list, a tap/press
                * anywhere on the header triggers a MENU_ACTION_CANCEL
                * action */
               else
                  return materialui_menu_entry_action(mui, entry, selection, MENU_ACTION_CANCEL);
            }
            /* Tap/press menu item: Activate and/or select item */
            else if ((ptr < entries_end) &&
                     (x   > mui->landscape_entry_margin) &&
                     (x   < width - mui->landscape_entry_margin - mui->nav_bar_layout_width))
            {
               if (gesture == MENU_INPUT_GESTURE_TAP)
               {
                  /* A 'tap' always produces a menu action */

                  /* If current 'pointer' item is not active,
                   * activate it immediately */
                  if (ptr != selection)
                     menu_navigation_set_selection(ptr);

                  /* Perform a MENU_ACTION_SELECT on currently
                   * active item */
                  return materialui_menu_entry_action(mui, entry, (size_t)ptr, MENU_ACTION_SELECT);
               }
               else
               {
                  /* A 'short' press is used only to activate (highlight)
                   * an item - it does not invoke a MENU_ACTION_SELECT
                   * action (this is intended for use in activating a
                   * settings-type entry, prior to swiping)
                   * Note: If everything is working correctly, the
                   * ptr item should already by selected at this stage
                   * - but menu_navigation_set_selection() just sets a
                   * variable, so there's no real point in performing
                   * a (selection != ptr) check here */
                  menu_navigation_set_selection(ptr);
                  menu_input_set_pointer_y_accel(0.0f);
               }
            }
         }
         break;
      case MENU_INPUT_GESTURE_LONG_PRESS:
         /* 'Reset to default' action */
         if ((ptr < entries_end) && (ptr == selection))
            return materialui_menu_entry_action(mui, entry, selection, MENU_ACTION_START);
         break;
      case MENU_INPUT_GESTURE_SWIPE_LEFT:
         {
            /* If we are at the top level, a swipe should
             * just switch between the three main menu screens
             * (i.e. we don't care which item is currently selected)
             * Note: For intuitive behaviour, a *left* swipe should
             * trigger a *right* navigation event */
            if (materialui_list_get_size(mui, MENU_LIST_PLAIN) == 1)
               return materialui_menu_entry_action(mui, entry, selection, MENU_ACTION_RIGHT);
            /* If we are displaying a playlist/file list/dropdown list,
             * swipes are used for fast navigation */
            else if (mui->is_playlist || mui->is_file_list || mui->is_dropdown_list)
               return materialui_pointer_up_swipe_horz_plain_list(
                     mui, entry, height, header_height, y,
                     selection, true);
            /* In all other cases, just perform a normal 'left'
             * navigation event */
            else
               return materialui_pointer_up_swipe_horz_default(
                     mui, entry, ptr, selection, entries_end, MENU_ACTION_LEFT);
         }
         break;
      case MENU_INPUT_GESTURE_SWIPE_RIGHT:
         {
            /* If we are at the top level, a swipe should
             * just switch between the three main menu screens
             * (i.e. we don't care which item is currently selected)
             * Note: For intuitive behaviour, a *right* swipe should
             * trigger a *left* navigation event */
            if (materialui_list_get_size(mui, MENU_LIST_PLAIN) == 1)
               return materialui_menu_entry_action(mui, entry, selection, MENU_ACTION_LEFT);
            /* If we are displaying a playlist/file list/dropdown list,
             * swipes are used for fast navigation */
            else if (mui->is_playlist || mui->is_file_list || mui->is_dropdown_list)
               return materialui_pointer_up_swipe_horz_plain_list(
                     mui, entry, height, header_height, y,
                     selection, false);
            /* In all other cases, just perform a normal 'right'
             * navigation event */
            else
               return materialui_pointer_up_swipe_horz_default(
                     mui, entry, ptr, selection, entries_end, MENU_ACTION_RIGHT);
         }
         break;
      default:
         /* Ignore input */
         break;
   }

   return 0;
}