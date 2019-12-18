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
typedef  void uint8_t ;
struct TYPE_3__ {size_t end; size_t size; size_t buffer; } ;
typedef  TYPE_1__ fifo_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 

void fifo_write(fifo_buffer_t *buffer, const void *in_buf, size_t size)
{
   size_t first_write = size;
   size_t rest_write  = 0;

   if (buffer->end + size > buffer->size)
   {
      first_write = buffer->size - buffer->end;
      rest_write  = size - first_write;
   }

   memcpy(buffer->buffer + buffer->end, in_buf, first_write);
   memcpy(buffer->buffer, (const uint8_t*)in_buf + first_write, rest_write);

   buffer->end = (buffer->end + size) % buffer->size;
}