#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_13__ {TYPE_1__** streams; } ;
struct TYPE_12__ {int nb_samples; scalar_t__ data; } ;
struct TYPE_11__ {int data; int size; } ;
struct TYPE_10__ {int /*<<< orphan*/  time_base; } ;
typedef  int /*<<< orphan*/  SwrContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_LOG_ERROR ; 
 int /*<<< orphan*/  audio_decode_fifo ; 
 size_t* audio_streams ; 
 size_t audio_streams_ptr ; 
 int av_frame_get_best_effort_timestamp (TYPE_3__*) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 scalar_t__ av_realloc (int /*<<< orphan*/ *,size_t) ; 
 int avcodec_decode_audio4 (int /*<<< orphan*/ *,TYPE_3__*,int*,TYPE_2__*) ; 
 int decode_last_audio_time ; 
 int /*<<< orphan*/  decode_thread_dead ; 
 TYPE_4__* fctx ; 
 int /*<<< orphan*/  fifo_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_cond ; 
 int /*<<< orphan*/  fifo_decode_cond ; 
 int /*<<< orphan*/  fifo_lock ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_cb (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  main_sleeping ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swr_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static int16_t *decode_audio(AVCodecContext *ctx, AVPacket *pkt,
      AVFrame *frame, int16_t *buffer, size_t *buffer_cap,
      SwrContext *swr)
{
   AVPacket pkt_tmp = *pkt;
   int got_ptr      = 0;

   for (;;)
   {
      int64_t pts;
      size_t required_buffer;
      int ret = avcodec_decode_audio4(ctx, frame, &got_ptr, &pkt_tmp);

      if (ret < 0)
         return buffer;

      pkt_tmp.data += ret;
      pkt_tmp.size -= ret;

      if (!got_ptr)
         break;

      required_buffer = frame->nb_samples * sizeof(int16_t) * 2;
      if (required_buffer > *buffer_cap)
      {
         buffer      = (int16_t*)av_realloc(buffer, required_buffer);
         *buffer_cap = required_buffer;
      }

      swr_convert(swr,
            (uint8_t**)&buffer,
            frame->nb_samples,
            (const uint8_t**)frame->data,
            frame->nb_samples);

      pts = av_frame_get_best_effort_timestamp(frame);
      slock_lock(fifo_lock);

      while (!decode_thread_dead && fifo_write_avail(audio_decode_fifo) < required_buffer)
      {
         if (!main_sleeping)
            scond_wait(fifo_decode_cond, fifo_lock);
         else
         {
            log_cb(RETRO_LOG_ERROR, "Thread: Audio deadlock detected ...\n");
            fifo_clear(audio_decode_fifo);
            break;
         }
      }

      decode_last_audio_time = pts * av_q2d(
            fctx->streams[audio_streams[audio_streams_ptr]]->time_base);

      if (!decode_thread_dead)
         fifo_write(audio_decode_fifo, buffer, required_buffer);

      scond_signal(fifo_cond);
      slock_unlock(fifo_lock);
   }

   return buffer;
}