#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {int running; int /*<<< orphan*/  cond; int /*<<< orphan*/  fifoLock; int /*<<< orphan*/  fifo; int /*<<< orphan*/  output; int /*<<< orphan*/  event; TYPE_1__ thread; } ;
typedef  TYPE_2__ switch_thread_audio_t ;
struct TYPE_10__ {size_t data_size; size_t buffer_size; scalar_t__ sample_data; scalar_t__ buffer; } ;
typedef  TYPE_3__ compat_audio_out_buffer ;
typedef  scalar_t__ Result ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,...) ; 
 scalar_t__ R_FAILED (scalar_t__) ; 
 int /*<<< orphan*/  U64_MAX ; 
 scalar_t__ audio_ipc_output_get_released_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**) ; 
 scalar_t__ audoutWaitPlayFinish (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_condvar_wake_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t fifo_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcGetCurrentProcessorNumber () ; 
 int /*<<< orphan*/  svcResetSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcSleepThread (int) ; 
 int /*<<< orphan*/  svcWaitSynchronization (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ switch_audio_ipc_output_append_buffer (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void mainLoop(void* data)
{
   Result rc;
   uint32_t released_out_count                  = 0;
   compat_audio_out_buffer *released_out_buffer = NULL;
   switch_thread_audio_t                  *swa  = (switch_thread_audio_t*)data;

   if (!swa)
      return;

   RARCH_LOG("[Audio]: start mainLoop cpu %u tid %u\n", svcGetCurrentProcessorNumber(), swa->thread.handle);

   while (swa->running)
   {
      size_t buf_avail, avail, to_write;

      if (!released_out_buffer)
      {
#ifdef HAVE_LIBNX
         rc = audoutWaitPlayFinish(&released_out_buffer, &released_out_count, U64_MAX);
#else
         uint32_t handle_idx = 0;
         svcWaitSynchronization(&handle_idx, &swa->event, 1, 33333333);
         svcResetSignal(swa->event);

         rc = audio_ipc_output_get_released_buffer(&swa->output, &released_out_count, &released_out_buffer);
#endif
         if (R_FAILED(rc))
         {
            swa->running = false;
            RARCH_LOG("[Audio]: audoutGetReleasedAudioOutBuffer failed: %d\n", (int)rc);
            break;
         }
         released_out_buffer->data_size = 0;
      }

      buf_avail = released_out_buffer->buffer_size - released_out_buffer->data_size;

      compat_mutex_lock(&swa->fifoLock);

      avail    = fifo_read_avail(swa->fifo);
      to_write = MIN(avail, buf_avail);
      if (to_write > 0)
      {
	      uint8_t *base;
#ifdef HAVE_LIBNX
	      base = (uint8_t*) released_out_buffer->buffer;
#else
	      base = (uint8_t*) released_out_buffer->sample_data;
#endif
         fifo_read(swa->fifo, base + released_out_buffer->data_size, to_write);
      }

      compat_mutex_unlock(&swa->fifoLock);
      compat_condvar_wake_all(&swa->cond);

      released_out_buffer->data_size += to_write;
      if (released_out_buffer->data_size >= released_out_buffer->buffer_size / 2)
      {
         rc = switch_audio_ipc_output_append_buffer(swa, released_out_buffer);
         if (R_FAILED(rc))
         {
            RARCH_LOG("[Audio]: audoutAppendAudioOutBuffer failed: %d\n", (int)rc);
         }
         released_out_buffer = NULL;
      }
      else
         svcSleepThread(16000000); /* 16ms */
   }
}