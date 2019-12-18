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
struct item_cheat {size_t idx; void* desc; void* code; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int size; struct item_cheat working_cheat; struct item_cheat* cheats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAT_HANDLER_TYPE_RETRO ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CHEAT_COPY_BEFORE_SUCCESS ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 int cheat_manager_get_size () ; 
 int /*<<< orphan*/  cheat_manager_realloc (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__ cheat_manager_state ; 
 int /*<<< orphan*/  memcpy (struct item_cheat*,struct item_cheat*,int) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strdup (void*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int action_ok_cheat_copy_before(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   int i;
   struct item_cheat tmp ;
   char msg[256] ;
   bool refresh = false ;
   unsigned int new_size = cheat_manager_get_size() + 1;
   cheat_manager_realloc(new_size, CHEAT_HANDLER_TYPE_RETRO);

   memcpy(&tmp, &cheat_manager_state.cheats[cheat_manager_state.working_cheat.idx], sizeof(struct item_cheat));
   tmp.idx = cheat_manager_state.working_cheat.idx ;
   if (tmp.code)
      tmp.code = strdup(tmp.code);
   if (tmp.desc)
      tmp.desc = strdup(tmp.desc);

   for (i = cheat_manager_state.size-2 ; i >=(int)tmp.idx ; i--)
   {
      memcpy(&cheat_manager_state.cheats[i+1], &cheat_manager_state.cheats[i], sizeof(struct item_cheat));
      cheat_manager_state.cheats[i+1].idx++ ;
   }

   memcpy(&cheat_manager_state.cheats[tmp.idx], &tmp, sizeof(struct item_cheat));
   memcpy(&cheat_manager_state.working_cheat, &tmp, sizeof(struct item_cheat));

   menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
   menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);

   strlcpy(msg, msg_hash_to_str(MSG_CHEAT_COPY_BEFORE_SUCCESS), sizeof(msg));
   msg[sizeof(msg) - 1] = 0;

   runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

   return 0 ;
}