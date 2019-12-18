#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_22__ {TYPE_6__* format; TYPE_3__* priv; } ;
typedef  TYPE_7__ VC_CONTAINER_TRACK_T ;
struct TYPE_23__ {TYPE_7__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_8__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_24__ {size_t current_track; } ;
typedef  TYPE_9__ VC_CONTAINER_MODULE_T ;
struct TYPE_21__ {int codec; scalar_t__ es_type; int extradata_size; int* extradata; TYPE_5__* type; } ;
struct TYPE_19__ {int bits_per_sample; int channels; unsigned int sample_rate; } ;
struct TYPE_20__ {TYPE_4__ audio; } ;
struct TYPE_18__ {TYPE_2__* module; } ;
struct TYPE_17__ {int object_type_indication; int sample_size; int /*<<< orphan*/  samples_batch_size; } ;
struct TYPE_16__ {TYPE_9__* module; } ;
typedef  int MP4_BOX_TYPE_T ;

/* Variables and functions */
#define  MP4_3GPP2_QCELP_OBJECT_TYPE 146 
 int MP4_BOX_TYPE_SOUN ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_STSD ; 
 int MP4_BOX_TYPE_TEXT ; 
 int MP4_BOX_TYPE_VIDE ; 
#define  MP4_JPEG_OBJECT_TYPE 145 
#define  MP4_KTF_MP3_OBJECT_TYPE 144 
 int /*<<< orphan*/  MP4_MAX_SAMPLES_BATCH_SIZE ; 
#define  MP4_MP3_OBJECT_TYPE 143 
#define  MP4_MPEG1_AUDIO_OBJECT_TYPE 142 
#define  MP4_MPEG1_VISUAL_OBJECT_TYPE 141 
#define  MP4_MPEG2_AAC_LC_OBJECT_TYPE 140 
#define  MP4_MPEG2_MP_OBJECT_TYPE 139 
#define  MP4_MPEG2_SNR_OBJECT_TYPE 138 
#define  MP4_MPEG2_SP_OBJECT_TYPE 137 
#define  MP4_MPEG4_AAC_LC_OBJECT_TYPE 136 
#define  MP4_MPEG4_VISUAL_OBJECT_TYPE 135 
 int MP4_READ_U32 (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U24 (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U8 (TYPE_8__*,char*) ; 
#define  MP4_SKT_EVRC_2V1_OBJECT_TYPE 134 
#define  MP4_SKT_EVRC_OBJECT_TYPE 133 
#define  VC_CONTAINER_CODEC_ALAW 132 
 int VC_CONTAINER_CODEC_EVRC ; 
 int VC_CONTAINER_CODEC_JPEG ; 
 int VC_CONTAINER_CODEC_MP1V ; 
 int VC_CONTAINER_CODEC_MP2V ; 
#define  VC_CONTAINER_CODEC_MP4A 131 
 int VC_CONTAINER_CODEC_MP4V ; 
 int VC_CONTAINER_CODEC_MPGA ; 
#define  VC_CONTAINER_CODEC_MULAW 130 
#define  VC_CONTAINER_CODEC_PCM_SIGNED_BE 129 
#define  VC_CONTAINER_CODEC_PCM_SIGNED_LE 128 
 int VC_CONTAINER_CODEC_QCELP ; 
 void* VC_CONTAINER_CODEC_UNKNOWN ; 
 scalar_t__ VC_CONTAINER_ERROR_CORRUPTED ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_SUBPICTURE ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ codec_needs_batch_mode (int) ; 
 int mp4_box_type_to_codec (int) ; 
 scalar_t__ mp4_read_box_data (TYPE_8__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp4_read_box_header (TYPE_8__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_read_box_stsd( VC_CONTAINER_T *p_ctx, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[module->current_track];
   VC_CONTAINER_STATUS_T status;
   MP4_BOX_TYPE_T box_type;
   int64_t box_size;
   uint32_t count;

   MP4_SKIP_U8(p_ctx, "version");
   MP4_SKIP_U24(p_ctx, "flags");

   count = MP4_READ_U32(p_ctx, "entry_count");
   if(!count) return VC_CONTAINER_ERROR_CORRUPTED;

   status = mp4_read_box_header( p_ctx, size, &box_type, &box_size );
   if(status != VC_CONTAINER_SUCCESS) return status;

   track->format->codec = mp4_box_type_to_codec(box_type);
   if(!track->format->codec) track->format->codec = box_type;

   if(track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO) box_type = MP4_BOX_TYPE_VIDE;
   if(track->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO) box_type = MP4_BOX_TYPE_SOUN;
   if(track->format->es_type == VC_CONTAINER_ES_TYPE_SUBPICTURE) box_type = MP4_BOX_TYPE_TEXT;
   status = mp4_read_box_data( p_ctx, box_type, box_size, MP4_BOX_TYPE_STSD );
   if(status != VC_CONTAINER_SUCCESS) return status;

   /* Special treatment for MPEG4 */
   if(track->format->codec == VC_CONTAINER_CODEC_MP4A)
   {
      switch (track->priv->module->object_type_indication)
      {
      case MP4_MPEG4_AAC_LC_OBJECT_TYPE:
      case MP4_MPEG2_AAC_LC_OBJECT_TYPE:
         track->format->codec = VC_CONTAINER_CODEC_MP4A; break;
      case MP4_MP3_OBJECT_TYPE:
      case MP4_MPEG1_AUDIO_OBJECT_TYPE:
      case MP4_KTF_MP3_OBJECT_TYPE:
         track->format->codec = VC_CONTAINER_CODEC_MPGA; break;
      case MP4_SKT_EVRC_2V1_OBJECT_TYPE:
      case MP4_SKT_EVRC_OBJECT_TYPE:
         track->format->codec = VC_CONTAINER_CODEC_EVRC; break;
      case MP4_3GPP2_QCELP_OBJECT_TYPE:
         track->format->codec = VC_CONTAINER_CODEC_QCELP; break;
      default:
         track->format->codec = VC_CONTAINER_CODEC_UNKNOWN; break;
      }
   }
   else if(track->format->codec == VC_CONTAINER_CODEC_MP4V)
   {
      switch (track->priv->module->object_type_indication)
      {
      case MP4_MPEG4_VISUAL_OBJECT_TYPE:
         track->format->codec = VC_CONTAINER_CODEC_MP4V; break;
      case MP4_JPEG_OBJECT_TYPE:
         track->format->codec = VC_CONTAINER_CODEC_JPEG; break;
      case MP4_MPEG2_SP_OBJECT_TYPE:
      case MP4_MPEG2_SNR_OBJECT_TYPE:
      case MP4_MPEG2_AAC_LC_OBJECT_TYPE:
      case MP4_MPEG2_MP_OBJECT_TYPE:
         track->format->codec = VC_CONTAINER_CODEC_MP2V; break;
      case MP4_MPEG1_VISUAL_OBJECT_TYPE:
         track->format->codec = VC_CONTAINER_CODEC_MP1V; break;
      default:
         track->format->codec = VC_CONTAINER_CODEC_UNKNOWN; break;
      }
   }

   /* For some codecs we process the samples in batches to be more efficient */
   if(codec_needs_batch_mode(track->format->codec))
      track->priv->module->samples_batch_size = MP4_MAX_SAMPLES_BATCH_SIZE;

   /* Fix-up some of the data */
   switch(track->format->codec)
   {
   case VC_CONTAINER_CODEC_ALAW:
   case VC_CONTAINER_CODEC_MULAW:
      track->format->type->audio.bits_per_sample = 8;
      track->priv->module->sample_size = track->format->type->audio.channels;
      break;
   case VC_CONTAINER_CODEC_PCM_SIGNED_LE:
   case VC_CONTAINER_CODEC_PCM_SIGNED_BE:
      track->priv->module->sample_size = (track->format->type->audio.bits_per_sample + 7) /
         8 * track->format->type->audio.channels;
      break;
   case VC_CONTAINER_CODEC_MP4A:
      /* samplerate / channels is sometimes invalid so sanity check it using the codec config data */
      if(track->format->extradata_size >= 2)
      {
         static unsigned int rate[] =
         { 96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050,
           16000, 12000, 11025, 8000, 7350 };
         unsigned int samplerate = 0, channels = 0;
         uint8_t *p = track->format->extradata;
         uint32_t index = (p[0] & 7) << 1 | (p[1] >> 7);
         if(index == 15 && track->format->extradata_size >= 5)
         {
            samplerate = (p[1] & 0x7f) << 17 | (p[2] << 9) | (p[3] << 1) | (p[4] >> 7);
            channels = (p[4] >> 3) & 15;
         }
         else if(index < 13)
         {
            samplerate = rate[index];
            channels = (p[1] >> 3) & 15;;
         }

         if(samplerate && samplerate != track->format->type->audio.sample_rate &&
               2 * samplerate != track->format->type->audio.sample_rate)
            track->format->type->audio.sample_rate = samplerate;
         if(channels && channels != track->format->type->audio.channels &&
               2 * channels != track->format->type->audio.channels)
            track->format->type->audio.channels = channels;
      }
      break;
   default: break;
   }

   return VC_CONTAINER_SUCCESS;
}