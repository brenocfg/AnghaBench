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
struct TYPE_2__ {int /*<<< orphan*/  setting; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 scalar_t__ file_list_get_actiondata_at_offset (int /*<<< orphan*/ *,size_t) ; 
 int menu_action_handle_setting (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 size_t menu_navigation_get_selection () ; 

int menu_setting_set(unsigned type, unsigned action, bool wraparound)
{
   int ret                    = 0;
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
   size_t selection           = menu_navigation_get_selection();
   menu_file_list_cbs_t *cbs  = selection_buf ?
      (menu_file_list_cbs_t*)file_list_get_actiondata_at_offset(selection_buf, selection) : NULL;

   if (!cbs)
      return 0;

   ret = menu_action_handle_setting(cbs->setting,
         type, action, wraparound);

   if (ret == -1)
      return 0;
   return ret;
}