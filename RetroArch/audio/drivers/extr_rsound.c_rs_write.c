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
struct TYPE_2__ {int /*<<< orphan*/  rd; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cond_lock; int /*<<< orphan*/  cond; scalar_t__ has_error; scalar_t__ nonblock; } ;
typedef  TYPE_1__ rsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsd_callback_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsd_callback_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t rs_write(void *data, const void *buf, size_t size)
{
   rsd_t *rsd = (rsd_t*)data;

   if (rsd->has_error)
      return -1;

   if (rsd->nonblock)
   {
      size_t avail, write_amt;

      rsd_callback_lock(rsd->rd);

      avail = fifo_write_avail(rsd->buffer);
      write_amt = avail > size ? size : avail;

      fifo_write(rsd->buffer, buf, write_amt);
      rsd_callback_unlock(rsd->rd);
      return write_amt;
   }
   else
   {
      size_t written = 0;
      while (written < size && !rsd->has_error)
      {
         size_t avail;
         rsd_callback_lock(rsd->rd);

         avail = fifo_write_avail(rsd->buffer);

         if (avail == 0)
         {
            rsd_callback_unlock(rsd->rd);
            if (!rsd->has_error)
            {
               slock_lock(rsd->cond_lock);
               scond_wait(rsd->cond, rsd->cond_lock);
               slock_unlock(rsd->cond_lock);
            }
         }
         else
         {
            size_t write_amt = size - written > avail ? avail : size - written;
            fifo_write(rsd->buffer, (const char*)buf + written, write_amt);
            rsd_callback_unlock(rsd->rd);
            written += write_amt;
         }
      }
      return written;
   }
}