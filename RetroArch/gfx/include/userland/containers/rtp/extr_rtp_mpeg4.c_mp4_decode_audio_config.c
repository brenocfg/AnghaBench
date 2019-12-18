#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {TYPE_4__* priv; TYPE_2__* format; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;
struct TYPE_13__ {int sample_rate; int channels; } ;
typedef  TYPE_6__ VC_CONTAINER_AUDIO_FORMAT_T ;
struct TYPE_11__ {TYPE_3__* module; } ;
struct TYPE_10__ {int timestamp_clock; } ;
struct TYPE_9__ {TYPE_1__* type; } ;
struct TYPE_8__ {TYPE_6__ audio; } ;

/* Variables and functions */
 int BITS_READ_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*,int) ; 
#define  MPEG4A_AAC_LC 128 

__attribute__((used)) static bool mp4_decode_audio_config(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      VC_CONTAINER_BITS_T *bit_stream)
{
   static uint32_t mp4_audio_sample_rate[] =
         { 96000, 88200, 64000, 48000, 44100, 32000, 24000,
           22050, 16000, 12000, 11025, 8000, 7350, 0, 0 };

   VC_CONTAINER_AUDIO_FORMAT_T *audio = &track->format->type->audio;
   uint32_t audio_object_type;
   uint32_t sampling_frequency_index;
   uint32_t channel_configuration;

   audio_object_type = BITS_READ_U32(p_ctx, bit_stream, 5, "audioObjectType");
   if (audio_object_type == 31)
      audio_object_type = BITS_READ_U32(p_ctx, bit_stream, 6, "audioObjectTypeExt") + 32;

   sampling_frequency_index = BITS_READ_U32(p_ctx, bit_stream, 4, "samplingFrequencyIndex");
   if (sampling_frequency_index == 0xF)
      audio->sample_rate = BITS_READ_U32(p_ctx, bit_stream, 24, "samplingFrequency");
   else
      audio->sample_rate = mp4_audio_sample_rate[sampling_frequency_index];
   if (!audio->sample_rate) return false;

   track->priv->module->timestamp_clock = audio->sample_rate;

   channel_configuration = BITS_READ_U32(p_ctx, bit_stream, 4, "channelConfiguration");
   switch (channel_configuration)
   {
   case 1:  /* 1 channel, centre front */
   case 2:  /* 2 channel, stereo front */
   case 3:  /* 3 channel, centre and stereo front */
   case 4:  /* 4 channel, centre and stereo front, mono surround */
   case 5:  /* 5 channel, centre and stereo front, stereo surround */
   case 6:  /* 5.1 channel, centre and stereo front, stereo surround, low freq */
      audio->channels = channel_configuration;
      break;
   case 7:  /* 7.1 channel, centre, stereo and stereo outside front, stereo surround, low freq */
      audio->channels = channel_configuration + 1;
      break;
   default:
      LOG_DEBUG(p_ctx, "MPEG-4: Unsupported channel configuration (%u)", channel_configuration);
      return false;
   }

   switch (audio_object_type)
   {
   case MPEG4A_AAC_LC:
      {
         uint32_t ga_specific_config = BITS_READ_U32(p_ctx, bit_stream, 3, "GASpecificConfig");

         /* Make sure there are no unexpected (and unsupported) additional configuration elements */
         if (ga_specific_config != 0)
         {
            LOG_DEBUG(p_ctx, "MPEG-4: Unexpected additional configuration data (%u)", ga_specific_config);
            return false;
         }
      }
      break;
   /* Add any further supported codecs here */
   default:
      LOG_DEBUG(p_ctx, "MPEG-4: Unsupported Audio Object Type (%u)", audio_object_type);
      return false;
   }

   return true;
}