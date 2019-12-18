#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* cue_buf; } ;
struct TYPE_7__ {scalar_t__ scheme; int hints; int fd; struct TYPE_7__* orig_path; struct TYPE_7__* buf; TYPE_1__ cdrom; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  mapped; scalar_t__ fp; } ;
typedef  TYPE_2__ libretro_vfs_implementation_file ;

/* Variables and functions */
 int RETRO_VFS_FILE_ACCESS_HINT_FREQUENT_ACCESS ; 
 int RFILE_HINT_UNBUFFERED ; 
 scalar_t__ VFS_SCHEME_CDROM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orbisClose (int) ; 
 int /*<<< orphan*/  retro_vfs_file_close_cdrom (TYPE_2__*) ; 

int retro_vfs_file_close_impl(libretro_vfs_implementation_file *stream)
{
   if (!stream)
      return -1;

#ifdef HAVE_CDROM
   if (stream->scheme == VFS_SCHEME_CDROM)
   {
      retro_vfs_file_close_cdrom(stream);
      goto end;
   }
#endif

   if ((stream->hints & RFILE_HINT_UNBUFFERED) == 0)
   {
      if (stream->fp)
      {
         fclose(stream->fp);
      }
   }
   else
   {
#ifdef HAVE_MMAP
      if (stream->hints & RETRO_VFS_FILE_ACCESS_HINT_FREQUENT_ACCESS)
         munmap(stream->mapped, stream->mapsize);
#endif
   }

   if (stream->fd > 0)
   {
#ifdef ORBIS
      orbisClose(stream->fd);
      stream->fd = -1;
#else
      close(stream->fd);
#endif
   }
#ifdef HAVE_CDROM
end:
   if (stream->cdrom.cue_buf)
      free(stream->cdrom.cue_buf);
#endif
   if (stream->buf)
      free(stream->buf);

   if (stream->orig_path)
      free(stream->orig_path);

   free(stream);

   return 0;
}