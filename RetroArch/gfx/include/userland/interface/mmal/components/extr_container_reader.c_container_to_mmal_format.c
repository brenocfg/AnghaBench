#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int flags; int /*<<< orphan*/  extradata; scalar_t__ extradata_size; TYPE_8__* type; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  codec_variant; int /*<<< orphan*/  codec; int /*<<< orphan*/  es_type; } ;
typedef  TYPE_9__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_23__ {int /*<<< orphan*/  block_align; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; } ;
struct TYPE_21__ {int /*<<< orphan*/  par_den; int /*<<< orphan*/  par_num; int /*<<< orphan*/  frame_rate_den; int /*<<< orphan*/  frame_rate_num; int /*<<< orphan*/  visible_height; int /*<<< orphan*/  visible_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_24__ {TYPE_7__ audio; TYPE_5__ video; } ;
struct TYPE_22__ {int /*<<< orphan*/  block_align; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; } ;
struct TYPE_19__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_18__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_17__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_20__ {TYPE_3__ par; TYPE_2__ frame_rate; TYPE_1__ crop; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_16__ {TYPE_6__ audio; TYPE_4__ video; } ;
struct TYPE_15__ {int type; scalar_t__ extradata_size; int /*<<< orphan*/  extradata; TYPE_12__* es; int /*<<< orphan*/  flags; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  encoding_variant; int /*<<< orphan*/  encoding; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_10__ MMAL_ES_FORMAT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 scalar_t__ MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ES_FORMAT_FLAG_FRAMED ; 
#define  MMAL_ES_TYPE_AUDIO 129 
 int MMAL_ES_TYPE_UNKNOWN ; 
#define  MMAL_ES_TYPE_VIDEO 128 
 scalar_t__ MMAL_SUCCESS ; 
 int VC_CONTAINER_ES_FORMAT_FLAG_FRAMED ; 
 int /*<<< orphan*/  container_to_mmal_encoding (int /*<<< orphan*/ ) ; 
 int container_to_mmal_es_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  container_to_mmal_variant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_12__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmal_format_extradata_alloc (TYPE_10__*,scalar_t__) ; 

__attribute__((used)) static MMAL_STATUS_T container_to_mmal_format(MMAL_ES_FORMAT_T *format,
   VC_CONTAINER_ES_FORMAT_T *container_format)
{
   format->type = container_to_mmal_es_type(container_format->es_type);
   if(format->type == MMAL_ES_TYPE_UNKNOWN)
      return MMAL_EINVAL;

   format->encoding = container_to_mmal_encoding(container_format->codec);
   format->encoding_variant = container_to_mmal_variant(container_format->codec, container_format->codec_variant);
   format->bitrate = container_format->bitrate;
   format->flags = (container_format->flags & VC_CONTAINER_ES_FORMAT_FLAG_FRAMED) ?
      MMAL_ES_FORMAT_FLAG_FRAMED : 0;
   memset(format->es, 0, sizeof(*format->es));

   switch(format->type)
   {
   case MMAL_ES_TYPE_VIDEO:
      format->es->video.width = container_format->type->video.width;
      format->es->video.height = container_format->type->video.height;
      format->es->video.crop.width = container_format->type->video.visible_width;
      format->es->video.crop.height = container_format->type->video.visible_height;
      format->es->video.frame_rate.num = container_format->type->video.frame_rate_num;
      format->es->video.frame_rate.den = container_format->type->video.frame_rate_den;
      format->es->video.par.num = container_format->type->video.par_num;
      format->es->video.par.den = container_format->type->video.par_den;
      break;
   case MMAL_ES_TYPE_AUDIO:
      format->es->audio.channels = container_format->type->audio.channels;
      format->es->audio.sample_rate = container_format->type->audio.sample_rate;
      format->es->audio.bits_per_sample = container_format->type->audio.bits_per_sample;
      format->es->audio.block_align = container_format->type->audio.block_align;
      break;
   default:
      LOG_ERROR("format es type not handled (%i)", (int)format->type);
      break;
   }

   if(container_format->extradata_size)
   {
      MMAL_STATUS_T status = mmal_format_extradata_alloc(format, container_format->extradata_size);
      if(status != MMAL_SUCCESS)
      {
         LOG_ERROR("couldn't allocate extradata");
         return status;
      }
      format->extradata_size = container_format->extradata_size;
      memcpy(format->extradata, container_format->extradata, format->extradata_size);
   }

   return MMAL_SUCCESS;
}