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
struct TYPE_7__ {int type; } ;
typedef  TYPE_2__ materialui_nav_bar_menu_tab_t ;
typedef  int /*<<< orphan*/  materialui_handle_t ;
struct TYPE_8__ {size_t size; TYPE_1__* list; } ;
typedef  TYPE_3__ file_list_t ;
struct TYPE_6__ {void* type; int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_MAIN_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLISTS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SETTINGS_TAB ; 
 int /*<<< orphan*/  MENU_LIST_PLAIN ; 
 void* MENU_PLAYLISTS_TAB ; 
 void* MENU_SETTINGS ; 
#define  MUI_NAV_BAR_MENU_TAB_MAIN 130 
#define  MUI_NAV_BAR_MENU_TAB_PLAYLISTS 129 
#define  MUI_NAV_BAR_MENU_TAB_SETTINGS 128 
 int /*<<< orphan*/  filebrowser_clear_type () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int materialui_list_get_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_flush_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* menu_entries_get_menu_stack_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool materialui_preswitch_tabs(
      materialui_handle_t *mui, materialui_nav_bar_menu_tab_t *target_tab)
{
   size_t stack_size       = 0;
   file_list_t *menu_stack = NULL;
   bool stack_flushed      = false;

   /* Pressing a navigation menu tab always returns us to
    * one of the top level menus. There are two ways to
    * implement this:
    * 1) Push a new menu list
    * 2) Reset the current menu stack, then switch
    *    to new menu
    * Option 1 seems like a good idea, since it means the
    * user's last menu position is remembered (so a back
    * action still works as expected after switching to the
    * new top level menu) - but the issue here is that the
    * menu stack can easily balloon to 'infinite' size,
    * which we simply cannot allow.
    * So we choose option 2 instead.
    * Thus, if the current menu stack size is greater than
    * 1, flush it all away...
    * Note: As far as I can tell, this if functionally
    * identical to just triggering multiple 'back' actions,
    * and so should be 'safe' */
   if (materialui_list_get_size(mui, MENU_LIST_PLAIN) > 1)
   {
      stack_flushed = true;
      menu_entries_flush_stack(msg_hash_to_str(MENU_ENUM_LABEL_MAIN_MENU), 0);
      /* Clear this, just in case... */
      filebrowser_clear_type();
   }

   /* Get current stack
    * (stack size should be zero here, but account
    * for unknown errors)  */
   menu_stack = menu_entries_get_menu_stack_ptr(0);
   stack_size = menu_stack->size;

   /* Sanity check
    * Note: if this fails, then 'stack flushed'
    * status is irrelevant... */
   if (stack_size < 1)
      return false;

   /* Delete existing label */
   if (menu_stack->list[stack_size - 1].label)
      free(menu_stack->list[stack_size - 1].label);
   menu_stack->list[stack_size - 1].label = NULL;

   /* Assign new label/type */
   switch (target_tab->type)
   {
      case MUI_NAV_BAR_MENU_TAB_PLAYLISTS:
         menu_stack->list[stack_size - 1].label =
            strdup(msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB));
         menu_stack->list[stack_size - 1].type =
            MENU_PLAYLISTS_TAB;
         break;
      case MUI_NAV_BAR_MENU_TAB_SETTINGS:
         menu_stack->list[stack_size - 1].label =
            strdup(msg_hash_to_str(MENU_ENUM_LABEL_SETTINGS_TAB));
         menu_stack->list[stack_size - 1].type =
            MENU_SETTINGS;
         break;
      case MUI_NAV_BAR_MENU_TAB_MAIN:
      default:
         menu_stack->list[stack_size - 1].label =
            strdup(msg_hash_to_str(MENU_ENUM_LABEL_MAIN_MENU));
         menu_stack->list[stack_size - 1].type =
            MENU_SETTINGS;
         break;
   }

   return stack_flushed;
}