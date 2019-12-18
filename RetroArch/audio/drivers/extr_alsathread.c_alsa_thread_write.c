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
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cond_lock; int /*<<< orphan*/  cond; scalar_t__ thread_dead; scalar_t__ nonblock; } ;
typedef  TYPE_1__ alsa_thread_t ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t alsa_thread_write(void *data, const void *buf, size_t size)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;

   if (alsa->thread_dead)
      return -1;

   if (alsa->nonblock)
   {
      size_t avail;
      size_t write_amt;

      slock_lock(alsa->fifo_lock);
      avail           = fifo_write_avail(alsa->buffer);
      write_amt       = MIN(avail, size);

      fifo_write(alsa->buffer, buf, write_amt);
      slock_unlock(alsa->fifo_lock);

      return write_amt;
   }
   else
   {
      size_t written = 0;
      while (written < size && !alsa->thread_dead)
      {
         size_t avail;
         slock_lock(alsa->fifo_lock);
         avail = fifo_write_avail(alsa->buffer);

         if (avail == 0)
         {
            slock_unlock(alsa->fifo_lock);
            slock_lock(alsa->cond_lock);
            if (!alsa->thread_dead)
               scond_wait(alsa->cond, alsa->cond_lock);
            slock_unlock(alsa->cond_lock);
         }
         else
         {
            size_t write_amt = MIN(size - written, avail);
            fifo_write(alsa->buffer,
                  (const char*)buf + written, write_amt);
            slock_unlock(alsa->fifo_lock);
            written += write_amt;
         }
      }
      return written;
   }
}