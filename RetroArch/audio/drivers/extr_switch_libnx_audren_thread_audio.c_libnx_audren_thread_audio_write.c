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
struct TYPE_2__ {int /*<<< orphan*/  fifo_condlock; int /*<<< orphan*/  fifo_condvar; int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  fifo; scalar_t__ running; scalar_t__ nonblocking; scalar_t__ paused; } ;
typedef  TYPE_1__ libnx_audren_thread_t ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  condvarWait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutexLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutexUnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t libnx_audren_thread_audio_write(void *data, const void *buf, size_t size)
{
   libnx_audren_thread_t *aud = (libnx_audren_thread_t*)data;
   size_t available, written, written_tmp;

   if (!aud || !aud->running)
      return -1;

   if(aud->paused)
      return 0;

   if(aud->nonblocking)
   {
      mutexLock(&aud->fifo_lock);
      available = fifo_write_avail(aud->fifo);
      written = MIN(available, size);
      if(written > 0)
      {
         fifo_write(aud->fifo, buf, written);
      }
      mutexUnlock(&aud->fifo_lock);
   }
   else
   {
      written = 0;
      while (written < size && aud->running)
      {
         mutexLock(&aud->fifo_lock);
         available = fifo_write_avail(aud->fifo);
         if(available)
         {
            written_tmp = MIN(size - written, available);
            fifo_write(aud->fifo, (const char*)buf + written, written_tmp);
            mutexUnlock(&aud->fifo_lock);
            written += written_tmp;
         }
         else
         {
            mutexUnlock(&aud->fifo_lock);
            mutexLock(&aud->fifo_condlock);
            condvarWait(&aud->fifo_condvar, &aud->fifo_condlock);
            mutexUnlock(&aud->fifo_condlock);
         }
      }
   }

   return written;
}