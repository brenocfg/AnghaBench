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
struct TYPE_3__ {int running; scalar_t__ fifo; struct TYPE_3__* mempool; int /*<<< orphan*/  drv; int /*<<< orphan*/  thread; int /*<<< orphan*/  fifo_lock; } ;
typedef  TYPE_1__ libnx_audren_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  audrenExit () ; 
 int /*<<< orphan*/  audrvClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audrvVoiceStop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_clear (scalar_t__) ; 
 int /*<<< orphan*/  fifo_free (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  mutexUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  threadClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  threadWaitForExit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void libnx_audren_thread_audio_free(void *data)
{
   libnx_audren_thread_t *aud = (libnx_audren_thread_t*)data;

   if (!aud)
      return;

   aud->running = false;
   mutexUnlock(&aud->fifo_lock);
   threadWaitForExit(&aud->thread);
   threadClose(&aud->thread);
   audrvVoiceStop(&aud->drv, 0);
   audrvClose(&aud->drv);
   audrenExit();

   if (aud->mempool)
   {
      free(aud->mempool);
   }

   if (aud->fifo)
   {
      fifo_clear(aud->fifo);
      fifo_free(aud->fifo);
   }

   free(aud);
}