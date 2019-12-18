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
struct TYPE_3__ {int /*<<< orphan*/  filebrowser_label; } ;
typedef  TYPE_1__ menu_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_FILE_BROWSER_SELECT_DIR ; 
 int /*<<< orphan*/  FILEBROWSER_SELECT_FILE ; 
 int /*<<< orphan*/  filebrowser_set_type (int /*<<< orphan*/ ) ; 
 int generic_action_ok_displaylist_push (char const*,int /*<<< orphan*/ *,char const*,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 
 int menu_cbs_exit () ; 
 TYPE_1__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int action_ok_push_filebrowser_list_file_select(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   menu_handle_t *menu       = menu_driver_get_ptr();

   if (!menu)
      return menu_cbs_exit();

   filebrowser_set_type(FILEBROWSER_SELECT_FILE);
   strlcpy(menu->filebrowser_label, label, sizeof(menu->filebrowser_label));
   return generic_action_ok_displaylist_push(path, NULL, label, type, idx,
         entry_idx, ACTION_OK_DL_FILE_BROWSER_SELECT_DIR);
}