#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond_mutex; } ;
struct TYPE_5__ {TYPE_1__ thread; int /*<<< orphan*/  fifo_buffer; int /*<<< orphan*/  thread_active; } ;
typedef  TYPE_2__ rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  RSD_DEBUG (char*) ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t rsnd_fill_buffer(rsound_t *rd, const char *buf, size_t size)
{

   /* Wait until we have a ready buffer */
   for (;;)
   {
      /* Should the thread be shut down while we're running, return with error */
      if ( !rd->thread_active )
         return 0;

      slock_lock(rd->thread.mutex);
      if ( fifo_write_avail(rd->fifo_buffer) >= size )
      {
         slock_unlock(rd->thread.mutex);
         break;
      }
      slock_unlock(rd->thread.mutex);

      /* Sleeps until we can write to the FIFO. */
      slock_lock(rd->thread.cond_mutex);
      scond_signal(rd->thread.cond);

      RSD_DEBUG("[RSound] rsnd_fill_buffer: Going to sleep.\n");
      scond_wait(rd->thread.cond, rd->thread.cond_mutex);
      RSD_DEBUG("[RSound] rsnd_fill_buffer: Woke up.\n");
      slock_unlock(rd->thread.cond_mutex);
   }

   slock_lock(rd->thread.mutex);
   fifo_write(rd->fifo_buffer, buf, size);
   slock_unlock(rd->thread.mutex);
   //RSD_DEBUG("[RSound] fill_buffer: Wrote to buffer.\n");

   /* Send signal to thread that buffer has been updated */
   //RSD_DEBUG("[RSound] fill_buffer: Waking up thread.\n");
   scond_signal(rd->thread.cond);

   return size;
}