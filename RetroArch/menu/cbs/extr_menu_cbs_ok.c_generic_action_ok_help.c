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
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
typedef  enum menu_dialog_type { ____Placeholder_menu_dialog_type } menu_dialog_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_HELP ; 
 int generic_action_ok_displaylist_push (char const*,int /*<<< orphan*/ *,char const*,int,size_t,size_t,int /*<<< orphan*/ ) ; 
 char* msg_hash_to_str (int) ; 

int  generic_action_ok_help(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx,
      enum msg_hash_enums id, enum menu_dialog_type id2)
{
   const char               *lbl  = msg_hash_to_str(id);

   return generic_action_ok_displaylist_push(path, NULL, lbl, id2, idx,
         entry_idx, ACTION_OK_DL_HELP);
}