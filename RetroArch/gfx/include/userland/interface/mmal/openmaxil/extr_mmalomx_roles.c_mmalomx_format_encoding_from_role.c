#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MMAL_FOURCC_T ;
typedef  int /*<<< orphan*/  MMAL_ES_TYPE_T ;
typedef  int MMALOMX_ROLE_T ;

/* Variables and functions */
#define  MMALOMX_ROLE_AUDIO_DECODER_AAC 141 
#define  MMALOMX_ROLE_AUDIO_DECODER_DDP 140 
#define  MMALOMX_ROLE_AUDIO_DECODER_MPGA_L1 139 
#define  MMALOMX_ROLE_AUDIO_DECODER_MPGA_L2 138 
#define  MMALOMX_ROLE_AUDIO_DECODER_MPGA_L3 137 
#define  MMALOMX_ROLE_VIDEO_DECODER_AVC 136 
#define  MMALOMX_ROLE_VIDEO_DECODER_H263 135 
#define  MMALOMX_ROLE_VIDEO_DECODER_MPEG2 134 
#define  MMALOMX_ROLE_VIDEO_DECODER_MPEG4 133 
#define  MMALOMX_ROLE_VIDEO_DECODER_VPX 132 
#define  MMALOMX_ROLE_VIDEO_DECODER_WMV 131 
#define  MMALOMX_ROLE_VIDEO_ENCODER_AVC 130 
#define  MMALOMX_ROLE_VIDEO_ENCODER_H263 129 
#define  MMALOMX_ROLE_VIDEO_ENCODER_MPEG4 128 
 int /*<<< orphan*/  MMAL_ENCODING_AC3 ; 
 int /*<<< orphan*/  MMAL_ENCODING_H263 ; 
 int /*<<< orphan*/  MMAL_ENCODING_H264 ; 
 int /*<<< orphan*/  MMAL_ENCODING_MP2V ; 
 int /*<<< orphan*/  MMAL_ENCODING_MP4A ; 
 int /*<<< orphan*/  MMAL_ENCODING_MP4V ; 
 int /*<<< orphan*/  MMAL_ENCODING_MPGA ; 
 int /*<<< orphan*/  MMAL_ENCODING_UNKNOWN ; 
 int /*<<< orphan*/  MMAL_ENCODING_VP8 ; 
 int /*<<< orphan*/  MMAL_ENCODING_WMV3 ; 
 int /*<<< orphan*/  MMAL_ES_TYPE_AUDIO ; 
 int /*<<< orphan*/  MMAL_ES_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  MMAL_ES_TYPE_VIDEO ; 

__attribute__((used)) static void mmalomx_format_encoding_from_role(MMALOMX_ROLE_T role,
   MMAL_FOURCC_T *encoding, MMAL_ES_TYPE_T *es_type, unsigned int *port)
{
   switch (role)
   {
   case MMALOMX_ROLE_VIDEO_DECODER_MPEG4:
   case MMALOMX_ROLE_VIDEO_ENCODER_MPEG4:
      *encoding = MMAL_ENCODING_MP4V;
      *es_type = MMAL_ES_TYPE_VIDEO;
      break;
   case MMALOMX_ROLE_VIDEO_DECODER_AVC:
   case MMALOMX_ROLE_VIDEO_ENCODER_AVC:
      *encoding = MMAL_ENCODING_H264;
      *es_type = MMAL_ES_TYPE_VIDEO;
      break;
   case MMALOMX_ROLE_VIDEO_DECODER_MPEG2:
      *encoding = MMAL_ENCODING_MP2V;
      *es_type = MMAL_ES_TYPE_VIDEO;
      break;
   case MMALOMX_ROLE_VIDEO_DECODER_WMV:
      *encoding = MMAL_ENCODING_WMV3;
      *es_type = MMAL_ES_TYPE_VIDEO;
      break;
   case MMALOMX_ROLE_VIDEO_DECODER_VPX:
      *encoding = MMAL_ENCODING_VP8;
      *es_type = MMAL_ES_TYPE_VIDEO;
      break;
   case MMALOMX_ROLE_VIDEO_DECODER_H263:
   case MMALOMX_ROLE_VIDEO_ENCODER_H263:
      *encoding = MMAL_ENCODING_H263;
      *es_type = MMAL_ES_TYPE_VIDEO;
      break;
   case MMALOMX_ROLE_AUDIO_DECODER_AAC:
      *encoding = MMAL_ENCODING_MP4A;
      *es_type = MMAL_ES_TYPE_AUDIO;
      break;
   case MMALOMX_ROLE_AUDIO_DECODER_MPGA_L1:
   case MMALOMX_ROLE_AUDIO_DECODER_MPGA_L2:
   case MMALOMX_ROLE_AUDIO_DECODER_MPGA_L3:
      *encoding = MMAL_ENCODING_MPGA;
      *es_type = MMAL_ES_TYPE_AUDIO;
      break;

   case MMALOMX_ROLE_AUDIO_DECODER_DDP:
      *encoding = MMAL_ENCODING_AC3;
      *es_type = MMAL_ES_TYPE_AUDIO;
      break;

   default:
      *encoding = MMAL_ENCODING_UNKNOWN;
      *es_type = MMAL_ES_TYPE_UNKNOWN;
      break;
   }

   switch (role)
   {
   case MMALOMX_ROLE_VIDEO_ENCODER_H263:
   case MMALOMX_ROLE_VIDEO_ENCODER_MPEG4:
   case MMALOMX_ROLE_VIDEO_ENCODER_AVC:
      *port = 1;
      break;
   default:
      *port = 0;
      break;
   }
}