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
 int filestream_rename_cb (char const*,char const*) ; 
 int retro_vfs_file_rename_impl (char const*,char const*) ; 

int filestream_rename(const char *old_path, const char *new_path)
{
   if (filestream_rename_cb != NULL)
      return filestream_rename_cb(old_path, new_path);

   return retro_vfs_file_rename_impl(old_path, new_path);
}