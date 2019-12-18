#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  eAMRBandMode; int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_25__ {int nSampleRate; int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_24__ {int nSamplingRate; int /*<<< orphan*/  eFormat; int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  nChannels; } ;
struct TYPE_23__ {int nSampleRate; int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_22__ {int nSampleRate; int /*<<< orphan*/  eAACStreamFormat; int /*<<< orphan*/  nBitRate; int /*<<< orphan*/  nChannels; } ;
struct TYPE_21__ {int nSamplingRate; int /*<<< orphan*/  ePCMMode; int /*<<< orphan*/  eNumData; int /*<<< orphan*/  eEndian; int /*<<< orphan*/  bInterleaved; int /*<<< orphan*/  nBitPerSample; int /*<<< orphan*/  nChannels; } ;
struct TYPE_17__ {int sample_rate; int /*<<< orphan*/  block_align; int /*<<< orphan*/  channels; int /*<<< orphan*/  bits_per_sample; } ;
struct TYPE_20__ {TYPE_12__ audio; } ;
struct TYPE_19__ {int nSampleRate; int /*<<< orphan*/  nDtsFrameSizeBytes; int /*<<< orphan*/  nChannels; } ;
struct TYPE_18__ {int nSampleRate; int /*<<< orphan*/  eBitStreamId; int /*<<< orphan*/  nChannels; } ;
struct TYPE_16__ {void* encoding; int /*<<< orphan*/  bitrate; scalar_t__ encoding_variant; TYPE_3__* es; } ;
struct TYPE_15__ {TYPE_2__ dts; TYPE_1__ ddp; TYPE_9__ amr; TYPE_8__ vorbis; TYPE_7__ wma; TYPE_6__ mp3; TYPE_5__ aac; TYPE_4__ pcm; } ;
typedef  TYPE_10__ OMX_FORMAT_PARAM_TYPE ;
typedef  int OMX_AUDIO_CODINGTYPE ;
typedef  void* MMAL_FOURCC_T ;
typedef  TYPE_11__ MMAL_ES_FORMAT_T ;
typedef  TYPE_12__ MMAL_AUDIO_FORMAT_T ;

/* Variables and functions */
 void* MMAL_ENCODING_ALAW ; 
 void* MMAL_ENCODING_AMRNB ; 
 void* MMAL_ENCODING_AMRWB ; 
 void* MMAL_ENCODING_EAC3 ; 
 void* MMAL_ENCODING_MP4A ; 
 void* MMAL_ENCODING_MPGA ; 
 void* MMAL_ENCODING_MULAW ; 
 void* MMAL_ENCODING_PCM_SIGNED_BE ; 
 void* MMAL_ENCODING_PCM_SIGNED_LE ; 
 void* MMAL_ENCODING_PCM_UNSIGNED_BE ; 
 void* MMAL_ENCODING_PCM_UNSIGNED_LE ; 
 scalar_t__ MMAL_ENCODING_VARIANT_MP4A_ADTS ; 
 scalar_t__ MMAL_ENCODING_VARIANT_MP4A_DEFAULT ; 
 void* MMAL_ENCODING_WMA1 ; 
 void* MMAL_ENCODING_WMA2 ; 
#define  OMX_AUDIO_AACStreamFormatMP2ADTS 162 
#define  OMX_AUDIO_AACStreamFormatMP4ADTS 161 
#define  OMX_AUDIO_AACStreamFormatMP4FF 160 
#define  OMX_AUDIO_AACStreamFormatRAW 159 
 int /*<<< orphan*/  OMX_AUDIO_AMRBandModeNB0 ; 
 int /*<<< orphan*/  OMX_AUDIO_AMRBandModeNB7 ; 
 int /*<<< orphan*/  OMX_AUDIO_AMRBandModeWB0 ; 
 int /*<<< orphan*/  OMX_AUDIO_AMRBandModeWB8 ; 
#define  OMX_AUDIO_CodingAAC 158 
#define  OMX_AUDIO_CodingADPCM 157 
#define  OMX_AUDIO_CodingAMR 156 
#define  OMX_AUDIO_CodingDDP 155 
#define  OMX_AUDIO_CodingDTS 154 
#define  OMX_AUDIO_CodingEVRC 153 
#define  OMX_AUDIO_CodingG711 152 
#define  OMX_AUDIO_CodingG723 151 
#define  OMX_AUDIO_CodingG726 150 
#define  OMX_AUDIO_CodingG729 149 
#define  OMX_AUDIO_CodingGSMEFR 148 
#define  OMX_AUDIO_CodingGSMFR 147 
#define  OMX_AUDIO_CodingGSMHR 146 
#define  OMX_AUDIO_CodingMIDI 145 
#define  OMX_AUDIO_CodingMP3 144 
#define  OMX_AUDIO_CodingPCM 143 
#define  OMX_AUDIO_CodingPDCEFR 142 
#define  OMX_AUDIO_CodingPDCFR 141 
#define  OMX_AUDIO_CodingPDCHR 140 
#define  OMX_AUDIO_CodingQCELP13 139 
#define  OMX_AUDIO_CodingQCELP8 138 
#define  OMX_AUDIO_CodingRA 137 
#define  OMX_AUDIO_CodingSBC 136 
#define  OMX_AUDIO_CodingSMV 135 
#define  OMX_AUDIO_CodingTDMAEFR 134 
#define  OMX_AUDIO_CodingTDMAFR 133 
#define  OMX_AUDIO_CodingVORBIS 132 
#define  OMX_AUDIO_CodingWMA 131 
 int /*<<< orphan*/  OMX_AUDIO_DDPBitStreamIdAC3 ; 
 int /*<<< orphan*/  OMX_AUDIO_PCMModeALaw ; 
 int /*<<< orphan*/  OMX_AUDIO_PCMModeLinear ; 
 int /*<<< orphan*/  OMX_AUDIO_PCMModeMULaw ; 
#define  OMX_AUDIO_WMAFormat7 130 
#define  OMX_AUDIO_WMAFormat8 129 
#define  OMX_AUDIO_WMAFormat9 128 
 int /*<<< orphan*/  OMX_EndianBig ; 
 int /*<<< orphan*/  OMX_EndianLittle ; 
 int /*<<< orphan*/  OMX_NumericalDataSigned ; 
 int /*<<< orphan*/  OMX_NumericalDataUnsigned ; 
 void* mmalil_omx_audio_coding_to_encoding (int) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

MMAL_FOURCC_T mmalil_omx_audio_param_to_format(MMAL_ES_FORMAT_T *format,
   OMX_AUDIO_CODINGTYPE coding, OMX_FORMAT_PARAM_TYPE *param)
{
   MMAL_AUDIO_FORMAT_T *audio = &format->es->audio;
   format->encoding = mmalil_omx_audio_coding_to_encoding(coding);
   format->encoding_variant = 0;

   switch(coding)
   {
   case OMX_AUDIO_CodingPCM:
      audio->channels = param->pcm.nChannels;
      audio->sample_rate = param->pcm.nSamplingRate;
      audio->bits_per_sample = param->pcm.nBitPerSample;
      if(param->pcm.ePCMMode == OMX_AUDIO_PCMModeLinear && param->pcm.bInterleaved)
      {
         if(param->pcm.eEndian == OMX_EndianBig &&
            param->pcm.eNumData == OMX_NumericalDataSigned)
            format->encoding = MMAL_ENCODING_PCM_SIGNED_BE;
         else if(param->pcm.eEndian == OMX_EndianLittle &&
            param->pcm.eNumData == OMX_NumericalDataSigned)
            format->encoding = MMAL_ENCODING_PCM_SIGNED_LE;
         if(param->pcm.eEndian == OMX_EndianBig &&
            param->pcm.eNumData == OMX_NumericalDataUnsigned)
            format->encoding = MMAL_ENCODING_PCM_UNSIGNED_BE;
         if(param->pcm.eEndian == OMX_EndianLittle &&
            param->pcm.eNumData == OMX_NumericalDataUnsigned)
            format->encoding = MMAL_ENCODING_PCM_UNSIGNED_LE;
      }
      else if(param->pcm.ePCMMode == OMX_AUDIO_PCMModeALaw)
         format->encoding = MMAL_ENCODING_ALAW;
      else if(param->pcm.ePCMMode == OMX_AUDIO_PCMModeMULaw)
         format->encoding = MMAL_ENCODING_MULAW;
      break;
   case OMX_AUDIO_CodingAAC:
      audio->channels = param->aac.nChannels;
      audio->sample_rate = param->aac.nSampleRate;
      format->bitrate = param->aac.nBitRate;
      switch(param->aac.eAACStreamFormat)
      {
      case OMX_AUDIO_AACStreamFormatMP2ADTS:
      case OMX_AUDIO_AACStreamFormatMP4ADTS:
         format->encoding = MMAL_ENCODING_MP4A;
         format->encoding_variant = MMAL_ENCODING_VARIANT_MP4A_ADTS;
         break;
      case OMX_AUDIO_AACStreamFormatMP4FF:
      case OMX_AUDIO_AACStreamFormatRAW:
         format->encoding = MMAL_ENCODING_MP4A;
         format->encoding_variant = MMAL_ENCODING_VARIANT_MP4A_DEFAULT;
         break;
      default: break;
      }
      break;
   case OMX_AUDIO_CodingMP3:
      format->encoding = MMAL_ENCODING_MPGA;
      audio->channels = param->mp3.nChannels;
      audio->sample_rate = param->mp3.nSampleRate;
      format->bitrate = param->mp3.nBitRate;
      break;
   case OMX_AUDIO_CodingWMA:
      audio->channels = param->wma.nChannels;
      audio->sample_rate = param->wma.nSamplingRate;
      audio->block_align = param->wma.nBlockAlign;
      format->bitrate = param->wma.nBitRate;
      switch(param->wma.eFormat)
      {
      case OMX_AUDIO_WMAFormat7:
         format->encoding = MMAL_ENCODING_WMA1;
         break;
      case OMX_AUDIO_WMAFormat8:
      case OMX_AUDIO_WMAFormat9:
         format->encoding = MMAL_ENCODING_WMA2;
         break;
      default: break;
      }
      break;
   case OMX_AUDIO_CodingVORBIS:
      audio->channels = param->vorbis.nChannels;
      audio->sample_rate = param->vorbis.nSampleRate;
      format->bitrate = param->vorbis.nBitRate;
      break;
   case OMX_AUDIO_CodingAMR:
      audio->channels = param->amr.nChannels;
      audio->sample_rate = 8000;
      format->bitrate = param->amr.nBitRate;
      if(param->amr.eAMRBandMode >= OMX_AUDIO_AMRBandModeNB0 &&
         param->amr.eAMRBandMode <= OMX_AUDIO_AMRBandModeNB7)
         format->encoding = MMAL_ENCODING_AMRNB;
      if(param->amr.eAMRBandMode >= OMX_AUDIO_AMRBandModeWB0 &&
         param->amr.eAMRBandMode <= OMX_AUDIO_AMRBandModeWB8)
         format->encoding = MMAL_ENCODING_AMRWB;
      break;
   case OMX_AUDIO_CodingDDP:
      audio->channels = param->ddp.nChannels;
      audio->sample_rate = param->ddp.nSampleRate;
      if(param->ddp.eBitStreamId > OMX_AUDIO_DDPBitStreamIdAC3)
         format->encoding = MMAL_ENCODING_EAC3;
      break;
   case OMX_AUDIO_CodingDTS:
      audio->channels = param->dts.nChannels;
      audio->sample_rate = param->dts.nSampleRate;
      audio->block_align = param->dts.nDtsFrameSizeBytes;
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

   return format->encoding;
}