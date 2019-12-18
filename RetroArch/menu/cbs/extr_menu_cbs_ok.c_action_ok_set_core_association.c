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
struct TYPE_3__ {int /*<<< orphan*/  rpl_entry_selection_ptr; } ;
typedef  TYPE_1__ menu_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_DEFERRED_CORE_LIST_SET ; 
 int generic_action_ok_displaylist_push (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int menu_cbs_exit () ; 
 TYPE_1__* menu_driver_get_ptr () ; 

__attribute__((used)) static int action_ok_set_core_association(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   menu_handle_t *menu                 = menu_driver_get_ptr();

   if (!menu)
      return menu_cbs_exit();

   /* TODO/FIXME - menu->rpl_entry_selection_ptr - find
    * a way so that we can remove this temporary state */
   return generic_action_ok_displaylist_push(path, NULL,
         NULL, 0, menu->rpl_entry_selection_ptr, entry_idx,
         ACTION_OK_DL_DEFERRED_CORE_LIST_SET);
}