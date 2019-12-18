#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int running; TYPE_4__* buffers; int /*<<< orphan*/ * fifo; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ switch_thread_audio_t ;
struct TYPE_6__ {int /*<<< orphan*/  sample_data; TYPE_1__* buffer; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  compat_thread_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_thread_join (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_audio_ipc_finalize () ; 
 int /*<<< orphan*/  switch_audio_ipc_output_stop (TYPE_1__*) ; 

__attribute__((used)) static void switch_thread_audio_free(void *data)
{
   unsigned i;
   switch_thread_audio_t *swa = (switch_thread_audio_t *)data;

   if (!swa)
         return;

   if (swa->running)
   {
         swa->running = false;
         compat_thread_join(&swa->thread);
         compat_thread_close(&swa->thread);
   }

   switch_audio_ipc_output_stop(swa);
   switch_audio_ipc_finalize();

   if (swa->fifo)
   {
         fifo_free(swa->fifo);
         swa->fifo = NULL;
   }

   for (i = 0; i < ARRAY_SIZE(swa->buffers); i++)
   {
#ifdef HAVE_LIBNX
         free(swa->buffers[i].buffer);
#else
         free_pages(swa->buffers[i].sample_data);
#endif
   }

   free(swa);
   swa = NULL;
}