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
struct ff_audio_info {int use_float; int is_planar; int sample_size; TYPE_1__* codec; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {int /*<<< orphan*/  sample_fmts; } ;
struct TYPE_4__ {void* sample_fmt; } ;
typedef  TYPE_2__ AVCodec ;

/* Variables and functions */
 void* AV_SAMPLE_FMT_FLT ; 
 void* AV_SAMPLE_FMT_FLTP ; 
 void* AV_SAMPLE_FMT_NONE ; 
 void* AV_SAMPLE_FMT_S16 ; 
 void* AV_SAMPLE_FMT_S16P ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 scalar_t__ ffmpeg_codec_has_sample_format (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmpeg_audio_resolve_format(struct ff_audio_info *audio,
      const AVCodec *codec)
{
   audio->codec->sample_fmt = AV_SAMPLE_FMT_NONE;

   if (ffmpeg_codec_has_sample_format(AV_SAMPLE_FMT_FLTP, codec->sample_fmts))
   {
      audio->codec->sample_fmt = AV_SAMPLE_FMT_FLTP;
      audio->use_float         = true;
      audio->is_planar         = true;
      RARCH_LOG("[FFmpeg]: Using sample format FLTP.\n");
   }
   else if (ffmpeg_codec_has_sample_format(AV_SAMPLE_FMT_FLT, codec->sample_fmts))
   {
      audio->codec->sample_fmt = AV_SAMPLE_FMT_FLT;
      audio->use_float         = true;
      audio->is_planar         = false;
      RARCH_LOG("[FFmpeg]: Using sample format FLT.\n");
   }
   else if (ffmpeg_codec_has_sample_format(AV_SAMPLE_FMT_S16P, codec->sample_fmts))
   {
      audio->codec->sample_fmt = AV_SAMPLE_FMT_S16P;
      audio->use_float         = false;
      audio->is_planar         = true;
      RARCH_LOG("[FFmpeg]: Using sample format S16P.\n");
   }
   else if (ffmpeg_codec_has_sample_format(AV_SAMPLE_FMT_S16, codec->sample_fmts))
   {
      audio->codec->sample_fmt = AV_SAMPLE_FMT_S16;
      audio->use_float         = false;
      audio->is_planar         = false;
      RARCH_LOG("[FFmpeg]: Using sample format S16.\n");
   }
   audio->sample_size = audio->use_float ? sizeof(float) : sizeof(int16_t);
}