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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_WRITE ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filestream_eof (int /*<<< orphan*/ *) ; 
 scalar_t__ filestream_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ filestream_read (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ filestream_write (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static bool file_copy(const char *src_path, const char *dst_path, char *msg, size_t size)
{
   RFILE *dst = NULL;
   bool ret   = true;
   RFILE *src = filestream_open(src_path,
         RETRO_VFS_FILE_ACCESS_READ,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);

   if (!src)
   {
      strlcpy(msg, "unable to open source file", size);
      ret = false;
   }

   dst = filestream_open(dst_path,
         RETRO_VFS_FILE_ACCESS_WRITE,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);

   if (!dst)
   {
      strlcpy(msg, "unable to open destination file", size);
      ret = false;
   }

   while (!filestream_eof(src))
   {
      int64_t numw;
      char buffer[100] = {0};
      int64_t numr = filestream_read(src, buffer, sizeof(buffer));

      if (filestream_error(dst) != 0)
      {
         strlcpy(msg, "error reading file\n", size);
         ret = false;
         break;
      }

      numw = filestream_write(dst, buffer, numr);

      if (numw != numr)
      {
         strlcpy(msg, "error writing to file\n", size);
         ret = false;
         break;
      }
   }

   filestream_close(src);
   filestream_close(dst);

   return ret;
}