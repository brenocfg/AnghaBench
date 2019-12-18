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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {int hints; scalar_t__ scheme; int mappos; int mapsize; int /*<<< orphan*/  fd; scalar_t__ mapped; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ libretro_vfs_implementation_file ;
typedef  int int64_t ;

/* Variables and functions */
 int RETRO_VFS_FILE_ACCESS_HINT_FREQUENT_ACCESS ; 
 int RFILE_HINT_UNBUFFERED ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 scalar_t__ VFS_SCHEME_CDROM ; 
 int _fseeki64 (int /*<<< orphan*/ ,int,int) ; 
 int fileXioLseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int fseek (int /*<<< orphan*/ ,long,int) ; 
 int fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int,int) ; 
 int orbisLseek (int /*<<< orphan*/ ,int,int) ; 
 int retro_vfs_file_seek_cdrom (TYPE_1__*,int,int) ; 

int64_t retro_vfs_file_seek_internal(libretro_vfs_implementation_file *stream, int64_t offset, int whence)
{
   if (!stream)
      return -1;

   if ((stream->hints & RFILE_HINT_UNBUFFERED) == 0)
   {
#ifdef HAVE_CDROM
      if (stream->scheme == VFS_SCHEME_CDROM)
         return retro_vfs_file_seek_cdrom(stream, offset, whence);
#endif
/* VC2005 and up have a special 64-bit fseek */
#ifdef ATLEAST_VC2005
      return _fseeki64(stream->fp, offset, whence);
#elif defined(__CELLOS_LV2__) || defined(_MSC_VER) && _MSC_VER <= 1310
      return fseek(stream->fp, (long)offset, whence);
#elif defined(PS2)
      {
         int64_t ret = fileXioLseek(fileno(stream->fp), (off_t)offset, whence);
         /* fileXioLseek could return positive numbers */
         if (ret > 0)
            return 0;
         return ret;
      }
#elif defined(ORBIS)
      {
         int ret = orbisLseek(stream->fd, offset, whence);
         if (ret < 0)
            return -1;
         return 0;
      }
#else
      return fseeko(stream->fp, (off_t)offset, whence);
#endif
   }
#ifdef HAVE_MMAP
   /* Need to check stream->mapped because this function is
    * called in filestream_open() */
   if (stream->mapped && stream->hints &
         RETRO_VFS_FILE_ACCESS_HINT_FREQUENT_ACCESS)
   {
      /* fseek() returns error on under/overflow but
       * allows cursor > EOF for
       read-only file descriptors. */
      switch (whence)
      {
         case SEEK_SET:
            if (offset < 0)
               return -1;

            stream->mappos = offset;
            break;

         case SEEK_CUR:
            if (  (offset < 0 && stream->mappos + offset > stream->mappos) ||
                  (offset > 0 && stream->mappos + offset < stream->mappos))
               return -1;

            stream->mappos += offset;
            break;

         case SEEK_END:
            if (stream->mapsize + offset < stream->mapsize)
               return -1;

            stream->mappos = stream->mapsize + offset;
            break;
      }
      return stream->mappos;
   }
#endif

   if (lseek(stream->fd, offset, whence) < 0)
      return -1;

   return 0;
}