#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  directory_core_assets; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_CONTENT_LIST ; 
 int /*<<< orphan*/  FILEBROWSER_SELECT_FILE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_FAVORITES ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  filebrowser_set_type (int /*<<< orphan*/ ) ; 
 int generic_action_ok_displaylist_push (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_ok_push_downloads_dir(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   settings_t            *settings   = config_get_ptr();

   filebrowser_set_type(FILEBROWSER_SELECT_FILE);
   return generic_action_ok_displaylist_push(path,
         settings->paths.directory_core_assets,
         msg_hash_to_str(MENU_ENUM_LABEL_FAVORITES),
         type, idx,
         entry_idx, ACTION_OK_DL_CONTENT_LIST);
}