#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int hints; scalar_t__ scheme; int mappos; int /*<<< orphan*/  fd; scalar_t__ mapped; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ libretro_vfs_implementation_file ;
typedef  int int64_t ;

/* Variables and functions */
 int RETRO_VFS_FILE_ACCESS_HINT_FREQUENT_ACCESS ; 
 int RFILE_HINT_UNBUFFERED ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ VFS_SCHEME_CDROM ; 
 int _ftelli64 (int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int orbisLseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int retro_vfs_file_tell_cdrom (TYPE_1__*) ; 

int64_t retro_vfs_file_tell_impl(libretro_vfs_implementation_file *stream)
{
   if (!stream)
      return -1;

   if ((stream->hints & RFILE_HINT_UNBUFFERED) == 0)
   {
#ifdef HAVE_CDROM
      if (stream->scheme == VFS_SCHEME_CDROM)
         return retro_vfs_file_tell_cdrom(stream);
#endif
#ifdef ORBIS
      {
         int64_t ret = orbisLseek(stream->fd, 0, SEEK_CUR);
         if (ret < 0)
            return -1;
         return ret;
      }
#else
      /* VC2005 and up have a special 64-bit ftell */
#ifdef ATLEAST_VC2005
      return _ftelli64(stream->fp);
#else
      return ftell(stream->fp);
#endif
#endif
   }
#ifdef HAVE_MMAP
   /* Need to check stream->mapped because this function
    * is called in filestream_open() */
   if (stream->mapped && stream->hints & RETRO_VFS_FILE_ACCESS_HINT_FREQUENT_ACCESS)
      return stream->mappos;
#endif
   if (lseek(stream->fd, 0, SEEK_CUR) < 0)
      return -1;

   return 0;
}