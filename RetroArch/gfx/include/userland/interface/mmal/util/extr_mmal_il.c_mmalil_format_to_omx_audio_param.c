#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nSampleRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_28__ {int /*<<< orphan*/  eFormat; int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  nSamplingRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_27__ {int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nSampleRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_26__ {int /*<<< orphan*/  eAACStreamFormat; int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nSampleRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_25__ {int /*<<< orphan*/  ePCMMode; int /*<<< orphan*/  eNumData; int /*<<< orphan*/  eEndian; int /*<<< orphan*/  bInterleaved; int /*<<< orphan*/  eChannelMapping; int /*<<< orphan*/  nBitPerSample; int /*<<< orphan*/  nSamplingRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_24__ {int /*<<< orphan*/  nSize; } ;
struct TYPE_20__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  block_align; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  bits_per_sample; } ;
struct TYPE_23__ {TYPE_13__ audio; } ;
struct TYPE_22__ {int nDtsType; int /*<<< orphan*/  eChannelMapping; int /*<<< orphan*/  nFormat; int /*<<< orphan*/  nDtsFrameSizeBytes; int /*<<< orphan*/  nSampleRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_21__ {int /*<<< orphan*/  eChannelMapping; int /*<<< orphan*/  eDolbySurroundMode; int /*<<< orphan*/  eBitStreamMode; int /*<<< orphan*/  eBitStreamId; int /*<<< orphan*/  nSampleRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_19__ {int /*<<< orphan*/  encoding; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  encoding_variant; TYPE_3__* es; } ;
struct TYPE_17__ {int /*<<< orphan*/  eAMRBandMode; int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_18__ {TYPE_2__ dts; TYPE_1__ ddp; TYPE_10__ amr; TYPE_9__ vorbis; TYPE_8__ wma; TYPE_7__ mp3; TYPE_6__ aac; TYPE_5__ pcm; TYPE_4__ common; } ;
typedef  int /*<<< orphan*/  OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_INDEXTYPE ;
typedef  TYPE_11__ OMX_FORMAT_PARAM_TYPE ;
typedef  int OMX_AUDIO_CODINGTYPE ;
typedef  TYPE_12__ MMAL_ES_FORMAT_T ;
typedef  TYPE_13__ MMAL_AUDIO_FORMAT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENCODING_ALAW ; 
 int /*<<< orphan*/  MMAL_ENCODING_AMRNB ; 
 int /*<<< orphan*/  MMAL_ENCODING_AMRWB ; 
 int /*<<< orphan*/  MMAL_ENCODING_EAC3 ; 
 int /*<<< orphan*/  MMAL_ENCODING_MULAW ; 
 int /*<<< orphan*/  MMAL_ENCODING_PCM_SIGNED_BE ; 
 int /*<<< orphan*/  MMAL_ENCODING_PCM_SIGNED_LE ; 
 int /*<<< orphan*/  MMAL_ENCODING_PCM_UNSIGNED_BE ; 
 int /*<<< orphan*/  MMAL_ENCODING_PCM_UNSIGNED_LE ; 
#define  MMAL_ENCODING_VARIANT_MP4A_ADTS 159 
#define  MMAL_ENCODING_VARIANT_MP4A_DEFAULT 158 
#define  MMAL_ENCODING_WMA1 157 
#define  MMAL_ENCODING_WMA2 156 
 int /*<<< orphan*/  OMX_AUDIO_AACStreamFormatMP4ADTS ; 
 int /*<<< orphan*/  OMX_AUDIO_AACStreamFormatRAW ; 
 int /*<<< orphan*/  OMX_AUDIO_AMRBandModeNB0 ; 
 int /*<<< orphan*/  OMX_AUDIO_AMRBandModeWB0 ; 
#define  OMX_AUDIO_CodingAAC 155 
#define  OMX_AUDIO_CodingADPCM 154 
#define  OMX_AUDIO_CodingAMR 153 
#define  OMX_AUDIO_CodingDDP 152 
#define  OMX_AUDIO_CodingDTS 151 
#define  OMX_AUDIO_CodingEVRC 150 
#define  OMX_AUDIO_CodingG711 149 
#define  OMX_AUDIO_CodingG723 148 
#define  OMX_AUDIO_CodingG726 147 
#define  OMX_AUDIO_CodingG729 146 
#define  OMX_AUDIO_CodingGSMEFR 145 
#define  OMX_AUDIO_CodingGSMFR 144 
#define  OMX_AUDIO_CodingGSMHR 143 
#define  OMX_AUDIO_CodingMIDI 142 
#define  OMX_AUDIO_CodingMP3 141 
#define  OMX_AUDIO_CodingPCM 140 
#define  OMX_AUDIO_CodingPDCEFR 139 
#define  OMX_AUDIO_CodingPDCFR 138 
#define  OMX_AUDIO_CodingPDCHR 137 
#define  OMX_AUDIO_CodingQCELP13 136 
#define  OMX_AUDIO_CodingQCELP8 135 
#define  OMX_AUDIO_CodingRA 134 
#define  OMX_AUDIO_CodingSBC 133 
#define  OMX_AUDIO_CodingSMV 132 
#define  OMX_AUDIO_CodingTDMAEFR 131 
#define  OMX_AUDIO_CodingTDMAFR 130 
#define  OMX_AUDIO_CodingVORBIS 129 
#define  OMX_AUDIO_CodingWMA 128 
 int /*<<< orphan*/  OMX_AUDIO_DDPBitStreamIdAC3 ; 
 int /*<<< orphan*/  OMX_AUDIO_DDPBitStreamIdEAC3 ; 
 int /*<<< orphan*/  OMX_AUDIO_PCMModeALaw ; 
 int /*<<< orphan*/  OMX_AUDIO_PCMModeLinear ; 
 int /*<<< orphan*/  OMX_AUDIO_PCMModeMULaw ; 
 int /*<<< orphan*/  OMX_AUDIO_WMAFormat7 ; 
 int /*<<< orphan*/  OMX_AUDIO_WMAFormat8 ; 
 int /*<<< orphan*/  OMX_EndianBig ; 
 int /*<<< orphan*/  OMX_EndianLittle ; 
 int /*<<< orphan*/  OMX_NumericalDataSigned ; 
 int /*<<< orphan*/  OMX_NumericalDataUnsigned ; 
 int /*<<< orphan*/  OMX_TRUE ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmalil_encoding_to_omx_audio_coding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalil_omx_audio_param_index (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmalil_omx_default_channel_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

OMX_AUDIO_CODINGTYPE mmalil_format_to_omx_audio_param(OMX_FORMAT_PARAM_TYPE *param,
   OMX_INDEXTYPE *param_index, MMAL_ES_FORMAT_T *format)
{
   MMAL_AUDIO_FORMAT_T *audio = &format->es->audio;
   OMX_AUDIO_CODINGTYPE coding = mmalil_encoding_to_omx_audio_coding(format->encoding);
   OMX_U32 size = 0;
   OMX_INDEXTYPE index = mmalil_omx_audio_param_index(coding, &size);

   if(param_index) *param_index = index;
   memset(param, 0, size);
   param->common.nSize = size;

   switch(coding)
   {
   case OMX_AUDIO_CodingPCM:
      param->pcm.nChannels = audio->channels;
      param->pcm.nSamplingRate = audio->sample_rate;
      param->pcm.nBitPerSample = audio->bits_per_sample;
      mmalil_omx_default_channel_mapping(param->pcm.eChannelMapping, audio->channels);
      if(format->encoding == MMAL_ENCODING_PCM_SIGNED_BE ||
         format->encoding == MMAL_ENCODING_PCM_SIGNED_LE ||
         format->encoding == MMAL_ENCODING_PCM_UNSIGNED_BE ||
         format->encoding == MMAL_ENCODING_PCM_UNSIGNED_LE)
      {
         param->pcm.ePCMMode = OMX_AUDIO_PCMModeLinear;
         param->pcm.bInterleaved = OMX_TRUE;
         param->pcm.eEndian = OMX_EndianLittle;
         param->pcm.eNumData = OMX_NumericalDataSigned;
         if(format->encoding == MMAL_ENCODING_PCM_SIGNED_BE ||
            format->encoding == MMAL_ENCODING_PCM_UNSIGNED_BE)
            param->pcm.eEndian = OMX_EndianBig;
         if(format->encoding == MMAL_ENCODING_PCM_UNSIGNED_LE ||
            format->encoding == MMAL_ENCODING_PCM_UNSIGNED_BE)
            param->pcm.eNumData = OMX_NumericalDataUnsigned;
      }
      else if(format->encoding == MMAL_ENCODING_ALAW)
         param->pcm.ePCMMode = OMX_AUDIO_PCMModeALaw;
      else if(format->encoding == MMAL_ENCODING_MULAW)
         param->pcm.ePCMMode = OMX_AUDIO_PCMModeMULaw;
      break;
   case OMX_AUDIO_CodingAAC:
      param->aac.nChannels = audio->channels;
      param->aac.nSampleRate = audio->sample_rate;
      param->aac.nBitRate = format->bitrate;
      switch(format->encoding_variant)
      {
      case MMAL_ENCODING_VARIANT_MP4A_ADTS:
         param->aac.eAACStreamFormat = OMX_AUDIO_AACStreamFormatMP4ADTS;
         break;
      case MMAL_ENCODING_VARIANT_MP4A_DEFAULT:
         param->aac.eAACStreamFormat = OMX_AUDIO_AACStreamFormatRAW;
         break;
      default: break;
      }
      break;
   case OMX_AUDIO_CodingMP3:
      param->mp3.nChannels = audio->channels;
      param->mp3.nSampleRate = audio->sample_rate;
      param->mp3.nBitRate = format->bitrate;
      break;
   case OMX_AUDIO_CodingWMA:
      param->wma.nChannels = audio->channels;
      param->wma.nSamplingRate = audio->sample_rate;
      param->wma.nBlockAlign = audio->block_align;
      param->wma.nBitRate = format->bitrate;
      switch(format->encoding)
      {
      case MMAL_ENCODING_WMA1:
         param->wma.eFormat = OMX_AUDIO_WMAFormat7;
         break;
      case MMAL_ENCODING_WMA2:
         param->wma.eFormat = OMX_AUDIO_WMAFormat8;
         break;
      default: break;
      }
      break;
   case OMX_AUDIO_CodingVORBIS:
      param->vorbis.nChannels = audio->channels;
      param->vorbis.nSampleRate = audio->sample_rate;
      param->vorbis.nBitRate = format->bitrate;
      break;
   case OMX_AUDIO_CodingAMR:
      param->amr.nChannels = audio->channels;
      param->amr.nBitRate = format->bitrate;
      if(format->encoding == MMAL_ENCODING_AMRNB)
         param->amr.eAMRBandMode = OMX_AUDIO_AMRBandModeNB0;
      if(format->encoding == MMAL_ENCODING_AMRWB)
         param->amr.eAMRBandMode = OMX_AUDIO_AMRBandModeWB0;
      break;
   case OMX_AUDIO_CodingDDP:
      param->ddp.nChannels = audio->channels;
      param->ddp.nSampleRate = audio->sample_rate;
      param->ddp.eBitStreamId = OMX_AUDIO_DDPBitStreamIdAC3;
      if(format->encoding == MMAL_ENCODING_EAC3)
         param->ddp.eBitStreamId = OMX_AUDIO_DDPBitStreamIdEAC3;
      param->ddp.eBitStreamMode = 0;
      param->ddp.eDolbySurroundMode = 0;
      mmalil_omx_default_channel_mapping(param->ddp.eChannelMapping, audio->channels);
      break;
   case OMX_AUDIO_CodingDTS:
      param->dts.nChannels = audio->channels;
      param->dts.nSampleRate = audio->sample_rate;
      param->dts.nDtsFrameSizeBytes = audio->block_align;
      param->dts.nDtsType = 1;
      param->dts.nFormat = 0;
      mmalil_omx_default_channel_mapping(param->dts.eChannelMapping, audio->channels);
      break;
   case OMX_AUDIO_CodingADPCM:
   case OMX_AUDIO_CodingGSMFR:
   case OMX_AUDIO_CodingGSMEFR:
   case OMX_AUDIO_CodingGSMHR:
   case OMX_AUDIO_CodingPDCFR:
   case OMX_AUDIO_CodingPDCEFR:
   case OMX_AUDIO_CodingPDCHR:
   case OMX_AUDIO_CodingTDMAFR:
   case OMX_AUDIO_CodingTDMAEFR:
   case OMX_AUDIO_CodingQCELP8:
   case OMX_AUDIO_CodingQCELP13:
   case OMX_AUDIO_CodingEVRC:
   case OMX_AUDIO_CodingSMV:
   case OMX_AUDIO_CodingG711:
   case OMX_AUDIO_CodingG723:
   case OMX_AUDIO_CodingG726:
   case OMX_AUDIO_CodingG729:
   case OMX_AUDIO_CodingSBC:
   case OMX_AUDIO_CodingRA:
   case OMX_AUDIO_CodingMIDI:
   default:
      vcos_assert(0);
      break;
   }

   return coding;
}