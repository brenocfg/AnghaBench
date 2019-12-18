#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ thumbnail_queue_size; scalar_t__ entry_has_thumbnail; int /*<<< orphan*/  show_fs_thumbnail; } ;
typedef  TYPE_1__ rgui_t ;
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;
typedef  int /*<<< orphan*/  menu_entry_t ;
typedef  enum menu_input_pointer_gesture { ____Placeholder_menu_input_pointer_gesture } menu_input_pointer_gesture ;
struct TYPE_5__ {scalar_t__ is_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ACTION_CANCEL ; 
 int /*<<< orphan*/  MENU_ACTION_SELECT ; 
 int /*<<< orphan*/  MENU_ACTION_START ; 
#define  MENU_INPUT_GESTURE_LONG_PRESS 130 
#define  MENU_INPUT_GESTURE_SHORT_PRESS 129 
#define  MENU_INPUT_GESTURE_TAP 128 
 TYPE_3__ fs_thumbnail ; 
 unsigned int menu_display_get_header_height () ; 
 int /*<<< orphan*/  menu_driver_navigation_set (int) ; 
 int /*<<< orphan*/  menu_entries_get_size () ; 
 int menu_entry_action (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  menu_navigation_set_selection (unsigned int) ; 
 int /*<<< orphan*/  rgui_update_thumbnail_image (TYPE_1__*) ; 

__attribute__((used)) static int rgui_pointer_up(void *data,
      unsigned x, unsigned y, unsigned ptr,
      enum menu_input_pointer_gesture gesture,
      menu_file_list_cbs_t *cbs,
      menu_entry_t *entry, unsigned action)
{
   rgui_t *rgui           = (rgui_t*)data;
   unsigned header_height = menu_display_get_header_height();
   size_t selection       = menu_navigation_get_selection();
   bool show_fs_thumbnail = false;

   if (!rgui)
      return -1;

   show_fs_thumbnail =
         rgui->show_fs_thumbnail &&
         rgui->entry_has_thumbnail &&
         (fs_thumbnail.is_valid || (rgui->thumbnail_queue_size > 0));

   switch (gesture)
   {
      case MENU_INPUT_GESTURE_TAP:
      case MENU_INPUT_GESTURE_SHORT_PRESS:
         {
            /* Normal pointer input */
            if (show_fs_thumbnail)
            {
               /* If we are currently showing a fullscreen thumbnail:
                * - Must provide a mechanism for toggling it off
                * - A normal mouse press should just select the current
                *   entry (for which the thumbnail is being shown) */
               if (y < header_height)
                  rgui_update_thumbnail_image(rgui);
               else
                  return menu_entry_action(entry, selection, MENU_ACTION_SELECT);
            }
            else
            {
               if (y < header_height)
                  return menu_entry_action(entry, selection, MENU_ACTION_CANCEL);
               else if (ptr <= (menu_entries_get_size() - 1))
               {
                  /* If currently selected item matches 'pointer' value,
                   * perform a MENU_ACTION_SELECT on it */
                  if (ptr == selection)
                     return menu_entry_action(entry, selection, MENU_ACTION_SELECT);

                  /* Otherwise, just move the current selection to the
                   * 'pointer' value */
                  menu_navigation_set_selection(ptr);
                  menu_driver_navigation_set(false);
               }
            }
         }
         break;
      case MENU_INPUT_GESTURE_LONG_PRESS:
         /* 'Reset to default' action */
         if ((ptr <= (menu_entries_get_size() - 1)) &&
             (ptr == selection))
            return menu_entry_action(entry, selection, MENU_ACTION_START);
         break;
      default:
         /* Ignore input */
         break;
   }

   return 0;
}