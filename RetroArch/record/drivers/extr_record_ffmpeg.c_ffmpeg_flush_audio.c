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
struct record_audio_data {size_t frames; void* data; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_11__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_10__ {int channels; } ;
struct TYPE_12__ {TYPE_2__ muxer; TYPE_1__ params; int /*<<< orphan*/  audio_fifo; } ;
typedef  TYPE_3__ ffmpeg_t ;
struct TYPE_13__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_4__ AVPacket ;

/* Variables and functions */
 scalar_t__ av_interleaved_write_frame (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  encode_audio (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ffmpeg_push_audio_thread (TYPE_3__*,struct record_audio_data*,int) ; 
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ ,void*,size_t) ; 
 size_t fifo_read_avail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmpeg_flush_audio(ffmpeg_t *handle, void *audio_buf,
      size_t audio_buf_size)
{
   size_t avail = fifo_read_avail(handle->audio_fifo);

   if (avail)
   {
      struct record_audio_data aud = {0};

      fifo_read(handle->audio_fifo, audio_buf, avail);

      aud.frames = avail / (sizeof(int16_t) * handle->params.channels);
      aud.data = audio_buf;

      ffmpeg_push_audio_thread(handle, &aud, false);
   }

   for (;;)
   {
      AVPacket pkt;
      if (!encode_audio(handle, &pkt, true) || !pkt.size ||
            av_interleaved_write_frame(handle->muxer.ctx, &pkt) < 0)
         break;
   }
}