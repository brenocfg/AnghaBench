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
struct TYPE_3__ {int running; struct TYPE_3__* zeroBuffer; int /*<<< orphan*/ * worker_thread; struct TYPE_3__* buffer; scalar_t__ cond_lock; scalar_t__ fifo_lock; scalar_t__ cond; } ;
typedef  TYPE_1__ psp_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  scond_free (scalar_t__) ; 
 int /*<<< orphan*/  slock_free (scalar_t__) ; 
 int /*<<< orphan*/  sthread_join (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psp_audio_free(void *data)
{
   psp_audio_t* psp = (psp_audio_t*)data;
   if(!psp)
      return;

   if(psp->running){
      if (psp->worker_thread)
      {
            psp->running = false;
            sthread_join(psp->worker_thread);
      }

      if (psp->cond)
            scond_free(psp->cond);
      if (psp->fifo_lock)
            slock_free(psp->fifo_lock);
      if (psp->cond_lock)
            slock_free(psp->cond_lock);
   }
   free(psp->buffer);
   psp->worker_thread = NULL;
   free(psp->zeroBuffer);
   free(psp);
}