#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int inited; int stopped_ack; scalar_t__ driver_data; TYPE_1__* driver; int /*<<< orphan*/  lock; int /*<<< orphan*/  is_shutdown; int /*<<< orphan*/  cond; scalar_t__ stopped; int /*<<< orphan*/  alive; int /*<<< orphan*/  use_float; int /*<<< orphan*/  new_rate; int /*<<< orphan*/  block_frames; int /*<<< orphan*/  latency; int /*<<< orphan*/  out_rate; int /*<<< orphan*/  device; } ;
typedef  TYPE_2__ audio_thread_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;int /*<<< orphan*/  (* start ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stop ) (scalar_t__) ;int /*<<< orphan*/  (* use_float ) (scalar_t__) ;scalar_t__ (* init ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  audio_driver_callback () ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (scalar_t__) ; 

__attribute__((used)) static void audio_thread_loop(void *data)
{
   audio_thread_t *thr = (audio_thread_t*)data;

   if (!thr)
      return;

   thr->driver_data   = thr->driver->init(
         thr->device, thr->out_rate, thr->latency,
         thr->block_frames, thr->new_rate);
   slock_lock(thr->lock);
   thr->inited        = thr->driver_data ? 1 : -1;
   if (thr->inited > 0 && thr->driver->use_float)
      thr->use_float  = thr->driver->use_float(thr->driver_data);
   scond_signal(thr->cond);
   slock_unlock(thr->lock);

   if (thr->inited < 0)
      return;

   /* Wait until we start to avoid calling
    * stop immediately after initialization. */
   slock_lock(thr->lock);
   while (thr->stopped)
      scond_wait(thr->cond, thr->lock);
   slock_unlock(thr->lock);

   for (;;)
   {
      slock_lock(thr->lock);

      if (!thr->alive)
      {
         scond_signal(thr->cond);
         thr->stopped_ack = true;
         slock_unlock(thr->lock);
         break;
      }

      if (thr->stopped)
      {
         thr->driver->stop(thr->driver_data);
         while (thr->stopped)
         {
            /* If we stop right after start, 
             * we might not be able to properly ack.
             * Signal in the loop instead. */
            thr->stopped_ack = true;
            scond_signal(thr->cond);

            scond_wait(thr->cond, thr->lock);
         }
         thr->driver->start(thr->driver_data, thr->is_shutdown);
      }

      slock_unlock(thr->lock);
      audio_driver_callback();
   }

   thr->driver->free(thr->driver_data);
}