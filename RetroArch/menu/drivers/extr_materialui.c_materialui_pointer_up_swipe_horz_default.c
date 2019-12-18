#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int path_enabled; int label_enabled; int rich_label_enabled; int sublabel_enabled; int /*<<< orphan*/  checked; } ;
typedef  TYPE_1__ menu_entry_t ;
struct TYPE_14__ {int /*<<< orphan*/  pointer_start_scroll_y; } ;
typedef  TYPE_2__ materialui_handle_t ;
typedef  enum msg_file_type { ____Placeholder_msg_file_type } msg_file_type ;
typedef  enum menu_action { ____Placeholder_menu_action } menu_action ;
typedef  enum materialui_entry_value_type { ____Placeholder_materialui_entry_value_type } materialui_entry_value_type ;

/* Variables and functions */
 int FILE_TYPE_NONE ; 
 int /*<<< orphan*/  MUI_ANIM_DURATION_SCROLL_RESET ; 
 int MUI_ENTRY_VALUE_NONE ; 
 int MUI_ENTRY_VALUE_SWITCH_OFF ; 
 int MUI_ENTRY_VALUE_SWITCH_ON ; 
 int MUI_ENTRY_VALUE_TEXT ; 
 int /*<<< orphan*/  materialui_animate_scroll (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int materialui_get_entry_value_type (TYPE_2__*,char const*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int materialui_menu_entry_action (TYPE_2__*,TYPE_1__*,size_t,int) ; 
 int /*<<< orphan*/  menu_entry_get (TYPE_1__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 unsigned int menu_entry_get_type_new (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_entry_get_value (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  menu_entry_init (TYPE_1__*) ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  msg_hash_calculate (char const*) ; 
 int msg_hash_to_file_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int materialui_pointer_up_swipe_horz_default(
      materialui_handle_t *mui, menu_entry_t *entry,
      unsigned ptr, size_t selection, size_t entries_end, enum menu_action action)
{
   int ret = 0;

   if ((ptr < entries_end) && (ptr == selection))
   {
      size_t new_selection = menu_navigation_get_selection();
      ret                  = materialui_menu_entry_action(
            mui, entry, selection, action);

      /* If we are changing a settings value, want to scroll
       * back to the 'pointer down' position. In all other cases
       * we do not. An entry is of the 'settings' type if:
       * - Selection pointer remains the same after MENU_ACTION event
       * - Entry value type is:
       *   > MUI_ENTRY_VALUE_TEXT
       *   > MUI_ENTRY_VALUE_SWITCH_ON
       *   > MUI_ENTRY_VALUE_SWITCH_OFF
       * Note: cannot use input (argument) entry, since this
       * will always have a blank value component */
      if (selection == new_selection)
      {
         const char *entry_value                           = NULL;
         unsigned entry_type                               = 0;
         enum msg_file_type entry_file_type                = FILE_TYPE_NONE;
         enum materialui_entry_value_type entry_value_type = MUI_ENTRY_VALUE_NONE;
         menu_entry_t last_entry;

         /* Get entry */
         menu_entry_init(&last_entry);
         last_entry.path_enabled       = false;
         last_entry.label_enabled      = false;
         last_entry.rich_label_enabled = false;
         last_entry.sublabel_enabled   = false;

         menu_entry_get(&last_entry, 0, selection, NULL, true);

         /* Parse entry */
         menu_entry_get_value(&last_entry, &entry_value);
         entry_type      = menu_entry_get_type_new(&last_entry);
         entry_file_type = msg_hash_to_file_type(msg_hash_calculate(entry_value));
         entry_value_type = materialui_get_entry_value_type(
               mui, entry_value, last_entry.checked, entry_type, entry_file_type);

         /* If entry has a 'settings' type, reset scroll position */
         if ((entry_value_type == MUI_ENTRY_VALUE_TEXT) ||
             (entry_value_type == MUI_ENTRY_VALUE_SWITCH_ON) ||
             (entry_value_type == MUI_ENTRY_VALUE_SWITCH_OFF))
            materialui_animate_scroll(
                  mui,
                  mui->pointer_start_scroll_y,
                  MUI_ANIM_DURATION_SCROLL_RESET);
      }
   }

   return ret;
}