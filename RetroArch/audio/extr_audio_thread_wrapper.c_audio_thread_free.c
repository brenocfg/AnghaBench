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
struct TYPE_3__ {int stopped; int alive; scalar_t__ cond; scalar_t__ lock; scalar_t__ thread; } ;
typedef  TYPE_1__ audio_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  scond_free (scalar_t__) ; 
 int /*<<< orphan*/  scond_signal (scalar_t__) ; 
 int /*<<< orphan*/  slock_free (scalar_t__) ; 
 int /*<<< orphan*/  slock_lock (scalar_t__) ; 
 int /*<<< orphan*/  slock_unlock (scalar_t__) ; 
 int /*<<< orphan*/  sthread_join (scalar_t__) ; 

__attribute__((used)) static void audio_thread_free(void *data)
{
   audio_thread_t *thr = (audio_thread_t*)data;

   if (!thr)
      return;

   if (thr->thread)
   {
      slock_lock(thr->lock);
      thr->stopped = false;
      thr->alive   = false;
      scond_signal(thr->cond);
      slock_unlock(thr->lock);

      sthread_join(thr->thread);
   }

   if (thr->lock)
      slock_free(thr->lock);
   if (thr->cond)
      scond_free(thr->cond);
   free(thr);
}