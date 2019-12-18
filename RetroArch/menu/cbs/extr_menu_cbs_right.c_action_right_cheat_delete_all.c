#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int delete_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAT_HANDLER_TYPE_EMU ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CHEAT_DELETE_ALL_SUCCESS ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 int /*<<< orphan*/  cheat_manager_realloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ cheat_manager_state ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int action_right_cheat_delete_all(unsigned type, const char *label,
      bool wraparound)
{
   bool refresh = false ;
   char msg[256];

   if ( ++cheat_manager_state.delete_state >= 5 )
   {
      msg[0] = '\0';
      cheat_manager_state.delete_state = 0 ;
      cheat_manager_realloc(0, CHEAT_HANDLER_TYPE_EMU) ;
      menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
      menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);

      strlcpy(msg,
            msg_hash_to_str(MSG_CHEAT_DELETE_ALL_SUCCESS), sizeof(msg));
      msg[sizeof(msg) - 1] = 0;

      runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   }

   return 0;
}