#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; scalar_t__ nonblock; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ coreaudio_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int g_interrupted ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t coreaudio_write(void *data, const void *buf_, size_t size)
{
   coreaudio_t *dev   = (coreaudio_t*)data;
   const uint8_t *buf = (const uint8_t*)buf_;
   size_t written     = 0;

   while (!g_interrupted && size > 0)
   {
      size_t write_avail;

      slock_lock(dev->lock);

      write_avail = fifo_write_avail(dev->buffer);
      if (write_avail > size)
         write_avail = size;

      fifo_write(dev->buffer, buf, write_avail);
      buf += write_avail;
      written += write_avail;
      size -= write_avail;

      if (dev->nonblock)
      {
         slock_unlock(dev->lock);
         break;
      }

#if TARGET_OS_IPHONE
      if (write_avail == 0 && !scond_wait_timeout(
               dev->cond, dev->lock, 3000000))
         g_interrupted = true;
#else
      if (write_avail == 0)
         scond_wait(dev->cond, dev->lock);
#endif
      slock_unlock(dev->lock);
   }

   return written;
}