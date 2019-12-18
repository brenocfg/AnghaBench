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
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {int start_time; int rate; int channels; int samplesize; int bytes_in_buffer; TYPE_1__ thread; int /*<<< orphan*/  fifo_buffer; scalar_t__ total_written; scalar_t__ has_written; } ;
typedef  TYPE_2__ rsound_t ;
typedef  int int64_t ;

/* Variables and functions */
 int fifo_read_avail (int /*<<< orphan*/ ) ; 
 int rsnd_get_time_usec () ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsnd_drain(rsound_t *rd)
{
   /* If the audio playback has started on the server we need to use timers. */
   if ( rd->has_written )
   {
      /* Calculates the amount of bytes that the server has consumed. */
      int64_t time = rsnd_get_time_usec();

      int64_t delta = time - rd->start_time;
      delta *= rd->rate * rd->channels * rd->samplesize;
      delta /= 1000000;
      /* Calculates the amount of data we have in our virtual buffer. Only used to calculate delay. */
      slock_lock(rd->thread.mutex);
      rd->bytes_in_buffer = (int)((int64_t)rd->total_written + (int64_t)fifo_read_avail(rd->fifo_buffer) - delta);
      slock_unlock(rd->thread.mutex);
   }
   else
   {
      slock_lock(rd->thread.mutex);
      rd->bytes_in_buffer = fifo_read_avail(rd->fifo_buffer);
      slock_unlock(rd->thread.mutex);
   }
}