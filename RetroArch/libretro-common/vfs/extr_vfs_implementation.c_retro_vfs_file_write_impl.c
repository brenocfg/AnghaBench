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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int hints; int /*<<< orphan*/  fd; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ libretro_vfs_implementation_file ;
typedef  int int64_t ;

/* Variables and functions */
 int RETRO_VFS_FILE_ACCESS_HINT_FREQUENT_ACCESS ; 
 int RFILE_HINT_UNBUFFERED ; 
 int fwrite (void const*,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ orbisWrite (int /*<<< orphan*/ ,void const*,size_t) ; 
 int write (int /*<<< orphan*/ ,void const*,size_t) ; 

int64_t retro_vfs_file_write_impl(libretro_vfs_implementation_file *stream, const void *s, uint64_t len)
{
   if (!stream)
      return -1;

   if ((stream->hints & RFILE_HINT_UNBUFFERED) == 0)
   {
#ifdef ORBIS
      if (orbisWrite(stream->fd, s, (size_t)len) < 0)
         return -1;
      return 0;
#else
      return fwrite(s, 1, (size_t)len, stream->fp);
#endif
   }

#ifdef HAVE_MMAP
   if (stream->hints & RETRO_VFS_FILE_ACCESS_HINT_FREQUENT_ACCESS)
      return -1;
#endif
   return write(stream->fd, s, (size_t)len);
}