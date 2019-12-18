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
typedef  int int64_t ;
struct TYPE_3__ {int offset; int track_end; } ;
typedef  TYPE_1__ chdstream_t ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 

int64_t chdstream_seek(chdstream_t *stream, int64_t offset, int whence)
{
   int64_t new_offset;

   switch (whence)
   {
      case SEEK_SET:
         new_offset = offset;
         break;
      case SEEK_CUR:
         new_offset = stream->offset + offset;
         break;
      case SEEK_END:
         new_offset = stream->track_end + offset;
         break;
      default:
         return -1;
   }

   if (new_offset < 0)
      return -1;

   if (new_offset > stream->track_end)
      new_offset = stream->track_end;

   stream->offset = new_offset;
   return 0;
}