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
typedef  int /*<<< orphan*/  libretro_vfs_implementation_file ;
typedef  int /*<<< orphan*/  cdrom_path_bin ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  cdrom_device_fillpath (char*,int,char const,int,int) ; 
 int cdrom_is_media_inserted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_get_vfs_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool cdrom_drive_has_media(const char drive)
{
   RFILE *file;
   char cdrom_path_bin[256] = {0};

   cdrom_device_fillpath(cdrom_path_bin, sizeof(cdrom_path_bin), drive, 1, false);

   file = filestream_open(cdrom_path_bin, RETRO_VFS_FILE_ACCESS_READ, 0);

   if (file)
   {
      libretro_vfs_implementation_file *stream = filestream_get_vfs_handle(file);
      bool has_media = false;

      has_media = cdrom_is_media_inserted(stream);

      filestream_close(file);

      return has_media;
   }

   return false;
}