#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int threads; TYPE_4__* packets; int /*<<< orphan*/  impl_data; TYPE_2__* thread_data; TYPE_1__* impl; } ;
typedef  TYPE_3__ rarch_softfilter_t ;
struct TYPE_9__ {int /*<<< orphan*/  thread_data; int /*<<< orphan*/  (* work ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int done; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; TYPE_4__* packet; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_work_packets ) (int /*<<< orphan*/ ,TYPE_4__*,void*,size_t,void const*,unsigned int,unsigned int,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*,void*,size_t,void const*,unsigned int,unsigned int,size_t) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rarch_softfilter_process(rarch_softfilter_t *filt,
      void *output, size_t output_stride,
      const void *input, unsigned width, unsigned height,
      size_t input_stride)
{
   unsigned i;

   if (!filt)
      return;

   if (filt->impl && filt->impl->get_work_packets)
      filt->impl->get_work_packets(filt->impl_data, filt->packets,
            output, output_stride, input, width, height, input_stride);

#ifdef HAVE_THREADS
   /* Fire off workers */
   for (i = 0; i < filt->threads; i++)
   {
#if 0
      RARCH_LOG("Firing off filter thread %u ...\n", i);
#endif
      filt->thread_data[i].packet = &filt->packets[i];
      slock_lock(filt->thread_data[i].lock);
      filt->thread_data[i].done = false;
      scond_signal(filt->thread_data[i].cond);
      slock_unlock(filt->thread_data[i].lock);
   }

   /* Wait for workers */
   for (i = 0; i < filt->threads; i++)
   {
#if 0
      RARCH_LOG("Waiting for filter thread %u ...\n", i);
#endif
      slock_lock(filt->thread_data[i].lock);
      while (!filt->thread_data[i].done)
         scond_wait(filt->thread_data[i].cond, filt->thread_data[i].lock);
      slock_unlock(filt->thread_data[i].lock);
   }
#else
   for (i = 0; i < filt->threads; i++)
      filt->packets[i].work(filt->impl_data, filt->packets[i].thread_data);
#endif
}