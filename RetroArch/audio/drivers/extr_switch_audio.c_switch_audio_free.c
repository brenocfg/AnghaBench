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
struct TYPE_5__ {int /*<<< orphan*/  output; TYPE_1__* buffers; int /*<<< orphan*/  is_paused; } ;
typedef  TYPE_2__ switch_audio_t ;
struct TYPE_4__ {TYPE_2__* buffer; } ;

/* Variables and functions */
 int BUFFER_COUNT ; 
 int /*<<< orphan*/  audio_ipc_finalize () ; 
 int /*<<< orphan*/  audio_ipc_output_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audoutExit () ; 
 int /*<<< orphan*/  audoutStopAudioOut () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void switch_audio_free(void *data)
{
   switch_audio_t *swa = (switch_audio_t*) data;

   if (!swa)
      return;

#ifdef HAVE_LIBNX
   if (!swa->is_paused)
      audoutStopAudioOut();

   audoutExit();

   int i;
   for (i = 0; i < BUFFER_COUNT; i++)
      free(swa->buffers[i].buffer);
#else
   audio_ipc_output_close(&swa->output);
   audio_ipc_finalize();
#endif
   free(swa);
}