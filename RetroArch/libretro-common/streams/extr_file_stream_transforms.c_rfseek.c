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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int RETRO_VFS_SEEK_POSITION_CURRENT ; 
 int RETRO_VFS_SEEK_POSITION_END ; 
 int RETRO_VFS_SEEK_POSITION_START ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  filestream_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int64_t rfseek(RFILE* stream, int64_t offset, int origin)
{
   int seek_position = -1;
   switch (origin)
   {
      case SEEK_SET:
         seek_position = RETRO_VFS_SEEK_POSITION_START;
         break;
      case SEEK_CUR:
         seek_position = RETRO_VFS_SEEK_POSITION_CURRENT;
         break;
      case SEEK_END:
         seek_position = RETRO_VFS_SEEK_POSITION_END;
         break;
   }

   return filestream_seek(stream, offset, seek_position);
}