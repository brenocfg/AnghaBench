#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int num_plugs; unsigned int threads; int die; scalar_t__ conf; struct TYPE_6__* thread_data; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; struct TYPE_6__* plugs; scalar_t__ lib; scalar_t__ impl_data; TYPE_1__* impl; struct TYPE_6__* packets; } ;
typedef  TYPE_2__ rarch_softfilter_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  config_file_free (scalar_t__) ; 
 int /*<<< orphan*/  dylib_close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sthread_join (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void rarch_softfilter_free(rarch_softfilter_t *filt)
{
   unsigned i = 0;
   (void)i;

   if (!filt)
      return;

   free(filt->packets);
   if (filt->impl && filt->impl_data)
      filt->impl->destroy(filt->impl_data);

#ifdef HAVE_DYLIB
   for (i = 0; i < filt->num_plugs; i++)
   {
      if (filt->plugs[i].lib)
         dylib_close(filt->plugs[i].lib);
   }
   free(filt->plugs);
#endif

#ifdef HAVE_THREADS
   for (i = 0; i < filt->threads; i++)
   {
      if (!filt->thread_data[i].thread)
         continue;
      slock_lock(filt->thread_data[i].lock);
      filt->thread_data[i].die = true;
      scond_signal(filt->thread_data[i].cond);
      slock_unlock(filt->thread_data[i].lock);
      sthread_join(filt->thread_data[i].thread);
      slock_free(filt->thread_data[i].lock);
      scond_free(filt->thread_data[i].cond);
   }
   free(filt->thread_data);
#endif

   if (filt->conf)
      config_file_free(filt->conf);

   free(filt);
}