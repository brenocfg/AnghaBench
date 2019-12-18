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
struct TYPE_3__ {int /*<<< orphan*/  action_select; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;
typedef  int /*<<< orphan*/  menu_entry_t ;
typedef  enum menu_input_pointer_gesture { ____Placeholder_menu_input_pointer_gesture } menu_input_pointer_gesture ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ACTION_CANCEL ; 
 int /*<<< orphan*/  MENU_ACTION_SELECT ; 
 int /*<<< orphan*/  MENU_ACTION_START ; 
#define  MENU_INPUT_GESTURE_LONG_PRESS 130 
#define  MENU_INPUT_GESTURE_SHORT_PRESS 129 
#define  MENU_INPUT_GESTURE_TAP 128 
 unsigned int menu_display_get_header_height () ; 
 int /*<<< orphan*/  menu_driver_navigation_set (int) ; 
 int /*<<< orphan*/  menu_entries_get_size () ; 
 int menu_entry_action (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  menu_navigation_set_selection (unsigned int) ; 

__attribute__((used)) static int stripes_pointer_up(void *userdata,
      unsigned x, unsigned y, unsigned ptr,
      enum menu_input_pointer_gesture gesture,
      menu_file_list_cbs_t *cbs,
      menu_entry_t *entry, unsigned action)
{
   size_t selection = menu_navigation_get_selection();

   switch (gesture)
   {
      case MENU_INPUT_GESTURE_TAP:
      case MENU_INPUT_GESTURE_SHORT_PRESS:
         {
            /* Normal pointer input */
            unsigned header_height = menu_display_get_header_height();

            if (y < header_height)
               return (unsigned)menu_entry_action(entry, selection, MENU_ACTION_CANCEL);
            else if (ptr <= (menu_entries_get_size() - 1))
            {
               if (ptr == selection && cbs && cbs->action_select)
                  return (unsigned)menu_entry_action(entry, selection, MENU_ACTION_SELECT);

               menu_navigation_set_selection(ptr);
               menu_driver_navigation_set(false);
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