#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_CONTENT_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_FAVORITES ; 
 int /*<<< orphan*/  free (char*) ; 
 int generic_action_ok_displaylist_push (char const*,char*,int /*<<< orphan*/ ,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 char* uwp_trigger_picker () ; 

__attribute__((used)) static int action_ok_open_picker(const char *path,
   const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   int ret;
#ifdef __WINRT__
   char *new_path = uwp_trigger_picker();
   if (!new_path)
      return 0; /* User aborted */
#else
   char *new_path = NULL;
   retro_assert(false);
#endif

   ret = generic_action_ok_displaylist_push(path, new_path,
      msg_hash_to_str(MENU_ENUM_LABEL_FAVORITES),
      type, idx,
      entry_idx, ACTION_OK_DL_CONTENT_LIST);

   free(new_path);
   return ret;
}