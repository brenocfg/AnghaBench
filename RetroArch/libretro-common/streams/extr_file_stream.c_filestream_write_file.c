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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_WRITE ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ filestream_write (int /*<<< orphan*/ *,void const*,scalar_t__) ; 

bool filestream_write_file(const char *path, const void *data, int64_t size)
{
   int64_t ret   = 0;
   RFILE *file   = filestream_open(path,
         RETRO_VFS_FILE_ACCESS_WRITE,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);
   if (!file)
      return false;

   ret = filestream_write(file, data, size);
   filestream_close(file);

   if (ret != size)
      return false;

   return true;
}