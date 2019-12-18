#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ es_type; int extradata_size; int* extradata; TYPE_12__* type; int /*<<< orphan*/  codec_variant; int /*<<< orphan*/  flags; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  codec; } ;
typedef  TYPE_8__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_22__ {int type; scalar_t__ encoding; int flags; int extradata_size; int* extradata; TYPE_7__* es; int /*<<< orphan*/  encoding_variant; int /*<<< orphan*/  bitrate; } ;
struct TYPE_19__ {int /*<<< orphan*/  block_align; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; } ;
struct TYPE_16__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_14__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_17__ {TYPE_3__ par; TYPE_1__ frame_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_20__ {TYPE_6__ audio; TYPE_4__ video; } ;
struct TYPE_18__ {int /*<<< orphan*/  block_align; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; } ;
struct TYPE_15__ {int /*<<< orphan*/  par_den; int /*<<< orphan*/  par_num; int /*<<< orphan*/  frame_rate_den; int /*<<< orphan*/  frame_rate_num; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_13__ {TYPE_5__ audio; TYPE_2__ video; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_9__ MMAL_ES_FORMAT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 scalar_t__ MMAL_ENCODING_H264 ; 
 int MMAL_ES_FORMAT_FLAG_FRAMED ; 
#define  MMAL_ES_TYPE_AUDIO 129 
#define  MMAL_ES_TYPE_VIDEO 128 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_FORMAT_FLAG_FRAMED ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  VC_CONTAINER_VARIANT_H264_AVC1 ; 
 int /*<<< orphan*/  memset (TYPE_12__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmal_to_container_encoding (scalar_t__) ; 
 scalar_t__ mmal_to_container_es_type (int) ; 
 int /*<<< orphan*/  mmal_to_container_variant (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_to_container_format(VC_CONTAINER_ES_FORMAT_T *container_format,
   MMAL_ES_FORMAT_T *format)
{
   container_format->es_type = mmal_to_container_es_type(format->type);
   if(container_format->es_type == VC_CONTAINER_ES_TYPE_UNKNOWN)
      return MMAL_EINVAL;

   container_format->codec = mmal_to_container_encoding(format->encoding);
   container_format->codec_variant = mmal_to_container_variant(format->encoding, format->encoding_variant);
   container_format->bitrate = format->bitrate;
   container_format->flags = 0;
   if(format->flags & MMAL_ES_FORMAT_FLAG_FRAMED)
      container_format->flags |= VC_CONTAINER_ES_FORMAT_FLAG_FRAMED;
   memset(container_format->type, 0, sizeof(*container_format->type));

   /* Auto-detect H264 AVC1 variant */
   if(format->encoding == MMAL_ENCODING_H264 && !format->encoding_variant &&
      format->extradata_size >= 5 && *format->extradata == 1)
      container_format->codec_variant = VC_CONTAINER_VARIANT_H264_AVC1;

   switch(format->type)
   {
   case MMAL_ES_TYPE_VIDEO:
      container_format->type->video.width = format->es->video.width;
      container_format->type->video.height = format->es->video.height;
      container_format->type->video.frame_rate_num = format->es->video.frame_rate.num;
      container_format->type->video.frame_rate_den = format->es->video.frame_rate.den;
      container_format->type->video.par_num = format->es->video.par.num;
      container_format->type->video.par_den = format->es->video.par.den;
      break;
   case MMAL_ES_TYPE_AUDIO:
      container_format->type->audio.channels = format->es->audio.channels;
      container_format->type->audio.sample_rate = format->es->audio.sample_rate;
      container_format->type->audio.bits_per_sample = format->es->audio.bits_per_sample;
      container_format->type->audio.block_align = format->es->audio.block_align;
      break;
   default:
      LOG_ERROR("format es type not handled (%i)", (int)format->type);
      break;
   }

   container_format->extradata_size = format->extradata_size;
   container_format->extradata = format->extradata;

   return MMAL_SUCCESS;
}