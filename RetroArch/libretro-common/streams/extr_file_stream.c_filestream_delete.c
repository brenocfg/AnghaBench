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
 int filestream_remove_cb (char const*) ; 
 int retro_vfs_file_remove_impl (char const*) ; 

int filestream_delete(const char *path)
{
   if (filestream_remove_cb != NULL)
      return filestream_remove_cb(path);

   return retro_vfs_file_remove_impl(path);
}