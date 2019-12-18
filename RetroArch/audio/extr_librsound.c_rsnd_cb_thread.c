#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t ssize_t ;
struct TYPE_14__ {size_t chunk_size; } ;
struct TYPE_13__ {int /*<<< orphan*/  thread; } ;
struct TYPE_12__ {int /*<<< orphan*/  socket; } ;
struct TYPE_15__ {size_t cb_max_size; size_t (* audio_callback ) (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ;int max_latency; int has_written; int total_written; int conn_type; int channels; int rate; int samplesize; TYPE_3__ backend_info; int /*<<< orphan*/  start_time; int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* error_callback ) (int /*<<< orphan*/ ) ;TYPE_2__ thread; TYPE_1__ conn; scalar_t__ thread_active; } ;
typedef  TYPE_4__ rsound_t ;

/* Variables and functions */
 int RSD_CONN_PROTO ; 
 int /*<<< orphan*/  RSD_DEBUG (char*,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  retro_sleep (int) ; 
 int /*<<< orphan*/  rsd_callback_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  rsd_callback_unlock (TYPE_4__*) ; 
 scalar_t__ rsd_delay_ms (TYPE_4__*) ; 
 int /*<<< orphan*/  rsd_delay_wait (TYPE_4__*) ; 
 int /*<<< orphan*/  rsnd_get_time_usec () ; 
 int /*<<< orphan*/  rsnd_reset (TYPE_4__*) ; 
 size_t rsnd_send_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  rsnd_send_info_query (TYPE_4__*) ; 
 int /*<<< orphan*/  rsnd_update_server_info (TYPE_4__*) ; 
 int /*<<< orphan*/  sthread_detach (int /*<<< orphan*/ ) ; 
 size_t stub1 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsnd_cb_thread(void *thread_data)
{
   rsound_t *rd = thread_data;
   size_t read_size = rd->backend_info.chunk_size;
   if (rd->cb_max_size != 0 && rd->cb_max_size < read_size)
      read_size = rd->cb_max_size;

   uint8_t buffer[rd->backend_info.chunk_size];

   while (rd->thread_active)
   {
      size_t has_read = 0;

      while (has_read < rd->backend_info.chunk_size)
      {
         size_t will_read = read_size < rd->backend_info.chunk_size - has_read ? read_size : rd->backend_info.chunk_size - has_read;

         rsd_callback_lock(rd);
         ssize_t ret = rd->audio_callback(buffer + has_read, will_read, rd->cb_data);
         rsd_callback_unlock(rd);

         if (ret < 0)
         {
            rsnd_reset(rd);
            sthread_detach(rd->thread.thread);
            rd->error_callback(rd->cb_data);
            return;
         }

         has_read += ret;

         if (ret < (ssize_t)will_read)
         {
            if ((int)rsd_delay_ms(rd) < rd->max_latency / 2)
            {
               RSD_DEBUG("[RSound] Callback thread: Requested %d bytes, got %d.\n", (int)will_read, (int)ret);
               memset(buffer + has_read, 0, will_read - ret);
               has_read += will_read - ret;
            }
            else
            {
               // The network might do things in large chunks, so it may request large amounts of data in short periods of time.
               // This breaks when the caller cannot buffer up big buffers beforehand, so do short sleeps inbetween.
               // This is somewhat dirty, but I cannot see a better solution
               retro_sleep(1);
            }
         }
      }

      ssize_t ret = rsnd_send_chunk(rd->conn.socket, buffer, rd->backend_info.chunk_size, 1);
      if (ret != (ssize_t)rd->backend_info.chunk_size)
      {
         rsnd_reset(rd);
         sthread_detach(rd->thread.thread);
         rd->error_callback(rd->cb_data);
         return;
      }

      /* If this was the first write, set the start point for the timer. */
      if (!rd->has_written)
      {
         rd->start_time = rsnd_get_time_usec();
         rd->has_written = 1;
      }

      rd->total_written += rd->backend_info.chunk_size;

      if ( (rd->conn_type & RSD_CONN_PROTO) && (rd->total_written > rd->channels * rd->rate * rd->samplesize) )
      {
         rsnd_send_info_query(rd);
         rsnd_update_server_info(rd);
      }

      if (rd->has_written)
         rsd_delay_wait(rd);
   }
}