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
 int /*<<< orphan*/  ACTION_OK_REMAP_FILE_REMOVE_CONTENT_DIR ; 
 int generic_action_ok_remap_file_operation (char const*,char const*,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_ok_remap_file_remove_content_dir(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   return generic_action_ok_remap_file_operation(path, label, type,
         idx, entry_idx, ACTION_OK_REMAP_FILE_REMOVE_CONTENT_DIR);
}