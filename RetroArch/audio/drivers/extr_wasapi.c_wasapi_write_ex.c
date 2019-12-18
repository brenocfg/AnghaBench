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
struct TYPE_4__ {size_t engine_buffer_size; int /*<<< orphan*/  buffer; scalar_t__ blocking; int /*<<< orphan*/  write_event; } ;
typedef  TYPE_1__ wasapi_t ;
typedef  int ssize_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,void const*,int) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wasapi_flush_buffer (TYPE_1__*,size_t) ; 

__attribute__((used)) static ssize_t wasapi_write_ex(wasapi_t *w, const void * data, size_t size)
{
   ssize_t written    = 0;
   size_t write_avail = fifo_write_avail(w->buffer);

   if (!write_avail)
   {
      DWORD ir = WaitForSingleObject(
            w->write_event, w->blocking ? INFINITE : 0);
      if (ir != WAIT_OBJECT_0)
      {
         if (w->blocking)
            return -1;
         return 0;
      }

      if (!wasapi_flush_buffer(w, w->engine_buffer_size))
         return -1;

      write_avail = w->engine_buffer_size;
   }

   written = size < write_avail ? size : write_avail;
   fifo_write(w->buffer, data, written);

   return written;
}