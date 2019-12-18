#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ff_config_param {int frame_drop_ratio; int audio_enable; int audio_global_quality; int scale_factor; int /*<<< orphan*/  format; int /*<<< orphan*/  audio_opts; int /*<<< orphan*/  video_opts; int /*<<< orphan*/  acodec; int /*<<< orphan*/  vcodec; void* out_pix_fmt; int /*<<< orphan*/  threads; } ;
struct TYPE_6__ {scalar_t__ video_record_scale_factor; scalar_t__ video_stream_scale_factor; scalar_t__ streaming_mode; int /*<<< orphan*/  video_record_threads; } ;
struct TYPE_5__ {int /*<<< orphan*/  video_gpu_record; } ;
struct TYPE_7__ {TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
 void* PIX_FMT_BGR24 ; 
 void* PIX_FMT_RGB24 ; 
 void* PIX_FMT_RGB8 ; 
 void* PIX_FMT_YUV420P ; 
#define  RECORD_CONFIG_TYPE_RECORDING_APNG 139 
#define  RECORD_CONFIG_TYPE_RECORDING_GIF 138 
#define  RECORD_CONFIG_TYPE_RECORDING_HIGH_QUALITY 137 
#define  RECORD_CONFIG_TYPE_RECORDING_LOSSLESS_QUALITY 136 
#define  RECORD_CONFIG_TYPE_RECORDING_LOW_QUALITY 135 
#define  RECORD_CONFIG_TYPE_RECORDING_MED_QUALITY 134 
#define  RECORD_CONFIG_TYPE_RECORDING_WEBM_FAST 133 
#define  RECORD_CONFIG_TYPE_RECORDING_WEBM_HIGH_QUALITY 132 
#define  RECORD_CONFIG_TYPE_STREAMING_HIGH_QUALITY 131 
#define  RECORD_CONFIG_TYPE_STREAMING_LOW_QUALITY 130 
#define  RECORD_CONFIG_TYPE_STREAMING_MED_QUALITY 129 
#define  RECORD_CONFIG_TYPE_STREAMING_NETPLAY 128 
 scalar_t__ STREAMING_MODE_TWITCH ; 
 scalar_t__ STREAMING_MODE_YOUTUBE ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool ffmpeg_init_config_common(struct ff_config_param *params, unsigned preset)
{
   settings_t *settings = config_get_ptr();

   switch (preset)
   {
      case RECORD_CONFIG_TYPE_RECORDING_LOW_QUALITY:
      case RECORD_CONFIG_TYPE_STREAMING_LOW_QUALITY:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 1;
         params->audio_enable         = true;
         params->audio_global_quality = 75;
         params->out_pix_fmt          = PIX_FMT_YUV420P;

         strlcpy(params->vcodec, "libx264", sizeof(params->vcodec));
         strlcpy(params->acodec, "aac", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "preset", "ultrafast", 0);
         av_dict_set(&params->video_opts, "tune", "film", 0);
         av_dict_set(&params->video_opts, "crf", "35", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "75", 0);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_MED_QUALITY:
      case RECORD_CONFIG_TYPE_STREAMING_MED_QUALITY:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 1;
         params->audio_enable         = true;
         params->audio_global_quality = 75;
         params->out_pix_fmt          = PIX_FMT_YUV420P;

         strlcpy(params->vcodec, "libx264", sizeof(params->vcodec));
         strlcpy(params->acodec, "aac", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "preset", "superfast", 0);
         av_dict_set(&params->video_opts, "tune", "film", 0);
         av_dict_set(&params->video_opts, "crf", "25", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "75", 0);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_HIGH_QUALITY:
      case RECORD_CONFIG_TYPE_STREAMING_HIGH_QUALITY:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 1;
         params->audio_enable         = true;
         params->audio_global_quality = 100;
         params->out_pix_fmt          = PIX_FMT_YUV420P;

         strlcpy(params->vcodec, "libx264", sizeof(params->vcodec));
         strlcpy(params->acodec, "aac", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "preset", "superfast", 0);
         av_dict_set(&params->video_opts, "tune", "film", 0);
         av_dict_set(&params->video_opts, "crf", "15", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "100", 0);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_LOSSLESS_QUALITY:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 1;
         params->audio_enable         = true;
         params->audio_global_quality = 80;
         params->out_pix_fmt          = PIX_FMT_BGR24;

         strlcpy(params->vcodec, "libx264rgb", sizeof(params->vcodec));
         strlcpy(params->acodec, "flac", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "qp", "0", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "100", 0);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_WEBM_FAST:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 1;
         params->audio_enable         = true;
         params->audio_global_quality = 50;
         params->out_pix_fmt          = PIX_FMT_YUV420P;

         strlcpy(params->vcodec, "libvpx", sizeof(params->vcodec));
         strlcpy(params->acodec, "libopus", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "deadline", "realtime", 0);
         av_dict_set(&params->video_opts, "crf", "14", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "50", 0);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_WEBM_HIGH_QUALITY:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 1;
         params->audio_enable         = true;
         params->audio_global_quality = 75;
         params->out_pix_fmt          = PIX_FMT_YUV420P;

         strlcpy(params->vcodec, "libvpx", sizeof(params->vcodec));
         strlcpy(params->acodec, "libopus", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "deadline", "realtime", 0);
         av_dict_set(&params->video_opts, "crf", "4", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "75", 0);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_GIF:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 4;
         params->audio_enable         = false;
         params->audio_global_quality = 0;
         params->out_pix_fmt          = PIX_FMT_RGB8;

         strlcpy(params->vcodec, "gif", sizeof(params->vcodec));
         strlcpy(params->acodec, "", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "framerate", "30", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "0", 0);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_APNG:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 1;
         params->audio_enable         = false;
         params->audio_global_quality = 0;
         params->out_pix_fmt          = PIX_FMT_RGB24;

         strlcpy(params->vcodec, "apng", sizeof(params->vcodec));
         strlcpy(params->acodec, "", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "pred", "avg", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "0", 0);
         break;
      case RECORD_CONFIG_TYPE_STREAMING_NETPLAY:
         params->threads              = settings->uints.video_record_threads;
         params->frame_drop_ratio     = 1;
         params->audio_enable         = true;
         params->audio_global_quality = 50;
         params->out_pix_fmt          = PIX_FMT_YUV420P;

         strlcpy(params->vcodec, "libx264", sizeof(params->vcodec));
         strlcpy(params->acodec, "aac", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "preset", "ultrafast", 0);
         av_dict_set(&params->video_opts, "tune", "zerolatency", 0);
         av_dict_set(&params->video_opts, "crf", "20", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "50", 0);

         /* TO-DO: detect if hwaccel is available and use it instead of the preset above
         strlcpy(params->vcodec, "h264_nvenc", sizeof(params->vcodec));
         strlcpy(params->acodec, "aac", sizeof(params->acodec));

         av_dict_set(&params->video_opts, "preset", "llhp", 0);
         av_dict_set(&params->video_opts, "tune", "zerolatency", 0);
         av_dict_set(&params->video_opts, "zerolatency", "1", 0);
         av_dict_set(&params->video_opts, "-rc-lookahead", "0", 0);
         av_dict_set(&params->video_opts, "x264-params", "threads=0:intra-refresh=1:b-frames=0", 0);
         av_dict_set(&params->audio_opts, "audio_global_quality", "100", 0);
         */

         break;
      default:
         break;
   }

   if (preset <= RECORD_CONFIG_TYPE_RECORDING_LOSSLESS_QUALITY)
   {
      if (!settings->bools.video_gpu_record)
         params->scale_factor = settings->uints.video_record_scale_factor > 0 ?
            settings->uints.video_record_scale_factor : 1;
      else
         params->scale_factor = 1;
      strlcpy(params->format, "matroska", sizeof(params->format));
   }
   else if (preset >= RECORD_CONFIG_TYPE_RECORDING_WEBM_FAST && preset < RECORD_CONFIG_TYPE_RECORDING_GIF)
   {
      if (!settings->bools.video_gpu_record)
         params->scale_factor = settings->uints.video_record_scale_factor > 0 ?
            settings->uints.video_record_scale_factor : 1;
      else
         params->scale_factor = 1;
      strlcpy(params->format, "webm", sizeof(params->format));
   }
   else if (preset >= RECORD_CONFIG_TYPE_RECORDING_GIF && preset < RECORD_CONFIG_TYPE_RECORDING_APNG)
   {
      if (!settings->bools.video_gpu_record)
         params->scale_factor = settings->uints.video_record_scale_factor > 0 ?
            settings->uints.video_record_scale_factor : 1;
      else
         params->scale_factor = 1;
      strlcpy(params->format, "gif", sizeof(params->format));
   }
   else if (preset < RECORD_CONFIG_TYPE_STREAMING_LOW_QUALITY)
   {
      params->scale_factor = 1;
      strlcpy(params->format, "apng", sizeof(params->format));
   }
   else if (preset <= RECORD_CONFIG_TYPE_STREAMING_HIGH_QUALITY)
   {
      if (!settings->bools.video_gpu_record)
         params->scale_factor = settings->uints.video_stream_scale_factor > 0 ?
            settings->uints.video_stream_scale_factor : 1;
      else
         params->scale_factor = 1;
      if (settings->uints.streaming_mode == STREAMING_MODE_YOUTUBE || settings->uints.streaming_mode == STREAMING_MODE_TWITCH)
         strlcpy(params->format, "flv", sizeof(params->format));
      else
         strlcpy(params->format, "mpegts", sizeof(params->format));
   }
   else if (preset == RECORD_CONFIG_TYPE_STREAMING_NETPLAY)
   {
      params->scale_factor = 1;
      strlcpy(params->format, "mpegts", sizeof(params->format));
   }

   return true;
}