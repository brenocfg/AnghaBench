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
struct TYPE_3__ {char* orig_path; int /*<<< orphan*/  fp; int /*<<< orphan*/  fh; } ;
typedef  TYPE_1__ libretro_vfs_implementation_file ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

int retro_vfs_file_close_cdrom(libretro_vfs_implementation_file *stream)
{
#ifdef CDROM_DEBUG
   printf("[CDROM] Close: Path %s\n", stream->orig_path);
   fflush(stdout);
#endif

#if defined(_WIN32) && !defined(_XBOX)
   if (!stream->fh || !CloseHandle(stream->fh))
      return -1;
#else
   if (!stream->fp || fclose(stream->fp))
      return -1;
#endif

   return 0;
}