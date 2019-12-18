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
struct item_cheat {size_t idx; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int size; struct item_cheat working_cheat; struct item_cheat* cheats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAT_HANDLER_TYPE_EMU ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CHEAT_ADD_BEFORE_SUCCESS ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 int cheat_manager_get_size () ; 
 int /*<<< orphan*/  cheat_manager_realloc (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__ cheat_manager_state ; 
 int /*<<< orphan*/  memcpy (struct item_cheat*,struct item_cheat*,int) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int action_ok_cheat_add_new_before(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   int i;
   char msg[256] ;
   struct item_cheat tmp ;
   bool refresh = false ;
   unsigned int new_size = cheat_manager_get_size() + 1;

   cheat_manager_realloc(new_size, CHEAT_HANDLER_TYPE_EMU);

   memcpy(&tmp, &cheat_manager_state.cheats[cheat_manager_state.size-1], sizeof(struct item_cheat));
   tmp.idx = cheat_manager_state.working_cheat.idx ;

   for (i = cheat_manager_state.size-2 ; i >=(int)tmp.idx ; i--)
   {
      memcpy(&cheat_manager_state.cheats[i+1], &cheat_manager_state.cheats[i], sizeof(struct item_cheat));
      cheat_manager_state.cheats[i+1].idx++ ;
   }

   memcpy(&cheat_manager_state.cheats[tmp.idx],
         &tmp, sizeof(struct item_cheat));
   memcpy(&cheat_manager_state.working_cheat,
         &tmp, sizeof(struct item_cheat));

   menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
   menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);

   strlcpy(msg, msg_hash_to_str(MSG_CHEAT_ADD_BEFORE_SUCCESS), sizeof(msg));
   msg[sizeof(msg) - 1] = 0;

   runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

   return 0 ;
}