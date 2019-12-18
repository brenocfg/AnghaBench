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
 int /*<<< orphan*/  ACTION_OK_SET_DIRECTORY ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 int /*<<< orphan*/  filebrowser_clear_type () ; 
 int generic_action_ok (int /*<<< orphan*/ *,char const*,unsigned int,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int action_ok_path_use_directory(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   filebrowser_clear_type();
   return generic_action_ok(NULL, label, type, idx, entry_idx,
         ACTION_OK_SET_DIRECTORY, MSG_UNKNOWN);
}