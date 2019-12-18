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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
#define  RETRO_VFS_SEEK_POSITION_CURRENT 130 
#define  RETRO_VFS_SEEK_POSITION_END 129 
#define  RETRO_VFS_SEEK_POSITION_START 128 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 int /*<<< orphan*/  retro_vfs_file_seek_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int64_t retro_vfs_file_seek_impl(libretro_vfs_implementation_file *stream,
      int64_t offset, int seek_position)
{
   int whence = -1;
   switch (seek_position)
   {
      case RETRO_VFS_SEEK_POSITION_START:
         whence = SEEK_SET;
         break;
      case RETRO_VFS_SEEK_POSITION_CURRENT:
         whence = SEEK_CUR;
         break;
      case RETRO_VFS_SEEK_POSITION_END:
         whence = SEEK_END;
         break;
   }

   return retro_vfs_file_seek_internal(stream, offset, whence);
}