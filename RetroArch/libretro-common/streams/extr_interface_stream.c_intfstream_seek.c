#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fp; } ;
struct TYPE_8__ {int /*<<< orphan*/  fp; } ;
struct TYPE_7__ {int /*<<< orphan*/  fp; } ;
struct TYPE_9__ {int type; TYPE_1__ chd; TYPE_3__ memory; TYPE_2__ file; } ;
typedef  TYPE_4__ intfstream_internal_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 133 
#define  INTFSTREAM_FILE 132 
#define  INTFSTREAM_MEMORY 131 
 int RETRO_VFS_SEEK_POSITION_CURRENT ; 
 int RETRO_VFS_SEEK_POSITION_END ; 
 int RETRO_VFS_SEEK_POSITION_START ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  chdstream_seek (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  filestream_seek (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memstream_seek (int /*<<< orphan*/ ,int,int) ; 

int64_t intfstream_seek(intfstream_internal_t *intf, int64_t offset, int whence)
{
   if (!intf)
      return -1;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         {
            int seek_position = 0;
            switch (whence)
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
            return (int64_t)filestream_seek(intf->file.fp, (int64_t)offset,
                  seek_position);
         }
      case INTFSTREAM_MEMORY:
         return (int64_t)memstream_seek(intf->memory.fp, offset, whence);
      case INTFSTREAM_CHD:
#ifdef HAVE_CHD
         return (int64_t)chdstream_seek(intf->chd.fp, offset, whence);
#else
         break;
#endif
   }

   return -1;
}