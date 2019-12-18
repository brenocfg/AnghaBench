#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ planar_buf; scalar_t__ fixed_conv; scalar_t__ resample_out; scalar_t__ float_conv; int /*<<< orphan*/ * resampler_data; TYPE_3__* resampler; scalar_t__ buffer; scalar_t__ codec; } ;
struct TYPE_10__ {scalar_t__ audio_opts; scalar_t__ video_opts; scalar_t__ conf; } ;
struct TYPE_9__ {scalar_t__ sws; int /*<<< orphan*/  scaler; scalar_t__ conv_frame_buf; int /*<<< orphan*/  conv_frame; scalar_t__ codec; } ;
struct TYPE_13__ {TYPE_4__ audio; TYPE_2__ config; TYPE_1__ video; } ;
typedef  TYPE_5__ ffmpeg_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (scalar_t__) ; 
 int /*<<< orphan*/  avcodec_close (scalar_t__) ; 
 int /*<<< orphan*/  config_file_free (scalar_t__) ; 
 int /*<<< orphan*/  deinit_thread (TYPE_5__*) ; 
 int /*<<< orphan*/  deinit_thread_buf (TYPE_5__*) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  scaler_ctx_gen_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_freeContext (scalar_t__) ; 

__attribute__((used)) static void ffmpeg_free(void *data)
{
   ffmpeg_t *handle = (ffmpeg_t*)data;
   if (!handle)
      return;

   deinit_thread(handle);
   deinit_thread_buf(handle);

   if (handle->audio.codec)
   {
      avcodec_close(handle->audio.codec);
      av_free(handle->audio.codec);
   }

   av_free(handle->audio.buffer);

   if (handle->video.codec)
   {
      avcodec_close(handle->video.codec);
      av_free(handle->video.codec);
   }

   av_frame_free(&handle->video.conv_frame);
   av_free(handle->video.conv_frame_buf);

   scaler_ctx_gen_reset(&handle->video.scaler);

   if (handle->video.sws)
      sws_freeContext(handle->video.sws);

   if (handle->config.conf)
      config_file_free(handle->config.conf);
   if (handle->config.video_opts)
      av_dict_free(&handle->config.video_opts);
   if (handle->config.audio_opts)
      av_dict_free(&handle->config.audio_opts);

   if (handle->audio.resampler && handle->audio.resampler_data)
      handle->audio.resampler->free(handle->audio.resampler_data);
   handle->audio.resampler      = NULL;
   handle->audio.resampler_data = NULL;

   av_free(handle->audio.float_conv);
   av_free(handle->audio.resample_out);
   av_free(handle->audio.fixed_conv);
   av_free(handle->audio.planar_buf);

   free(handle);
}