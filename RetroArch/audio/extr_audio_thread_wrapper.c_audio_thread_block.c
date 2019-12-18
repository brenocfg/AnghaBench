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
struct TYPE_3__ {int stopped; int stopped_ack; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ audio_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audio_thread_block(audio_thread_t *thr)
{
   if (!thr)
      return;

   if (thr->stopped)
      return;

   slock_lock(thr->lock);
   thr->stopped_ack = false;
   thr->stopped = true;
   scond_signal(thr->cond);

   /* Wait until audio driver actually goes to sleep. */
   while (!thr->stopped_ack)
      scond_wait(thr->cond, thr->lock);

   slock_unlock(thr->lock);
}