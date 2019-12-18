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
typedef  int /*<<< orphan*/  cdfs_track_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/ * cdfs_wrap_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intfstream_open_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* path_get_extension (char const*) ; 
 scalar_t__ string_is_equal_noncase (char const*,char*) ; 

cdfs_track_t* cdfs_open_raw_track(const char* path)
{
   const char* ext = path_get_extension(path);

   if (string_is_equal_noncase(ext, "bin") || string_is_equal_noncase(ext, "iso"))
      return cdfs_wrap_stream(intfstream_open_file(path, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE), 0);

   /* unsupported file type */
   return NULL;
}