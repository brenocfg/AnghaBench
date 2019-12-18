#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int latency; int /*<<< orphan*/  last_append; TYPE_4__* current_buffer; int /*<<< orphan*/  event; scalar_t__ blocking; } ;
typedef  TYPE_1__ switch_audio_t ;
typedef  int ssize_t ;
struct TYPE_7__ {int data_size; size_t buffer_size; scalar_t__ buffer; scalar_t__ sample_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  U64_MAX ; 
 scalar_t__ audoutWaitPlayFinish (TYPE_4__**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  svcGetSystemTick () ; 
 int /*<<< orphan*/  svcResetSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcWaitSynchronization (int*,int /*<<< orphan*/ *,int,int) ; 
 size_t switch_audio_buffer_size (int /*<<< orphan*/ *) ; 
 scalar_t__ switch_audio_ipc_output_append_buffer (TYPE_1__*,TYPE_4__*) ; 
 scalar_t__ switch_audio_ipc_output_get_released_buffer (TYPE_1__*,int) ; 

__attribute__((used)) static ssize_t switch_audio_write(void *data, const void *buf, size_t size)
{
   size_t to_write     = size;
	switch_audio_t *swa = (switch_audio_t*) data;

   if (!swa)
      return -1;

	if (!swa->current_buffer)
   {
      uint32_t num;
      if (switch_audio_ipc_output_get_released_buffer(swa, num) != 0)
      {
         RARCH_LOG("Failed to get released buffer?\n");
         return -1;
      }

      if (num < 1)
         swa->current_buffer = NULL;

      if (!swa->current_buffer)
      {
         if (swa->blocking)
         {
            while(swa->current_buffer == NULL)
            {
               uint32_t handle_idx = 0;
               num                 = 0;

#ifdef HAVE_LIBNX
               if (audoutWaitPlayFinish(&swa->current_buffer, &num, U64_MAX) != 0) { }
#else
               svcWaitSynchronization(&handle_idx, &swa->event, 1, 33333333);
               svcResetSignal(swa->event);

               if (switch_audio_ipc_output_get_released_buffer(swa, num) != 0)
                  return -1;
#endif
            }
         }
         else
            /* no buffer, nonblocking... */
            return 0;
      }

      swa->current_buffer->data_size = 0;
   }

	if (to_write > switch_audio_buffer_size(NULL) - swa->current_buffer->data_size)
		to_write = switch_audio_buffer_size(NULL) - swa->current_buffer->data_size;

   #ifndef HAVE_LIBNX
	memcpy(((uint8_t*) swa->current_buffer->sample_data) + swa->current_buffer->data_size, buf, to_write);
   #else
	memcpy(((uint8_t*) swa->current_buffer->buffer) + swa->current_buffer->data_size, buf, to_write);
   #endif
	swa->current_buffer->data_size   += to_write;
	swa->current_buffer->buffer_size  = switch_audio_buffer_size(NULL);

	if (swa->current_buffer->data_size > (48000 * swa->latency) / 1000)
   {
         if (switch_audio_ipc_output_append_buffer(swa, swa->current_buffer) != 0)
            return -1;
		swa->current_buffer = NULL;
	}

	swa->last_append = svcGetSystemTick();

	return to_write;
}