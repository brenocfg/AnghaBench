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

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_CB_CORE_CONTENT_DOWNLOAD ; 
 int MSG_UNKNOWN ; 
 int action_ok_download_generic (char const*,char const*,char const*,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_get_last_stack (char const**,char const**,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_ok_core_content_download(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   const char *menu_path   = NULL;
   const char *menu_label  = NULL;
   enum msg_hash_enums enum_idx = MSG_UNKNOWN;

   menu_entries_get_last_stack(&menu_path, &menu_label, NULL, &enum_idx, NULL);

   return action_ok_download_generic(path, label,
         menu_path, type, idx, entry_idx,
         MENU_ENUM_LABEL_CB_CORE_CONTENT_DOWNLOAD);
}