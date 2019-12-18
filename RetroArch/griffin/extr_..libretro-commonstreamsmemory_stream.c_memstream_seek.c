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
struct TYPE_3__ {int ptr; int max_ptr; int size; int /*<<< orphan*/  writing; } ;
typedef  TYPE_1__ memstream_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 

int64_t memstream_seek(memstream_t *stream, int64_t offset, int whence)
{
   uint64_t ptr;

   switch (whence)
   {
      case SEEK_SET:
         ptr = offset;
         break;
      case SEEK_CUR:
         ptr = stream->ptr + offset;
         break;
      case SEEK_END:
         ptr = (stream->writing ? stream->max_ptr : stream->size) + offset;
         break;
      default:
         return -1;
   }

   if (ptr <= stream->size)
   {
      stream->ptr = ptr;
      return 0;
   }

   return -1;
}