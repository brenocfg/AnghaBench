#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_16__ {int /*<<< orphan*/  is_enabled; TYPE_6__* format; TYPE_2__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_T ;
struct TYPE_17__ {int tracks_num; TYPE_3__** tracks; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_18__ {int extradata_size; scalar_t__ extradata; int /*<<< orphan*/  flags; int /*<<< orphan*/  group_id; scalar_t__ language; int /*<<< orphan*/  bitrate; int /*<<< orphan*/ * type; int /*<<< orphan*/  codec_variant; int /*<<< orphan*/  codec; int /*<<< orphan*/  es_type; } ;
typedef  TYPE_6__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_15__ {int /*<<< orphan*/  is_enabled; TYPE_6__* format; scalar_t__ meta_num; } ;
struct TYPE_14__ {TYPE_1__* module; } ;
struct TYPE_13__ {TYPE_5__* reader; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (TYPE_5__*,char*,int) ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 scalar_t__ vc_container_track_allocate_extradata (TYPE_5__*,TYPE_4__*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_copy_track_data_from_reader( VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track )
{
   VC_CONTAINER_T *reader = track->priv->module->reader;
   VC_CONTAINER_ES_FORMAT_T *src_format, *dst_format;

   if (reader->tracks_num != 1)
   {
      LOG_ERROR(p_ctx, "RTSP: Expected track reader to have one track, has %d", reader->tracks_num);
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }

   if (reader->tracks[0]->meta_num)
   {
      LOG_DEBUG(p_ctx, "RTSP: Track reader has meta data - not supported");
   }

   src_format = reader->tracks[0]->format;
   dst_format = track->format;

   /* Copy fields individually to avoid problems with pointers (type and extradata). */
   dst_format->es_type        = src_format->es_type;
   dst_format->codec          = src_format->codec;
   dst_format->codec_variant  = src_format->codec_variant;
   *dst_format->type          = *src_format->type;
   dst_format->bitrate        = src_format->bitrate;
   memcpy(dst_format->language, src_format->language, sizeof(dst_format->language));
   dst_format->group_id       = src_format->group_id;
   dst_format->flags          = src_format->flags;

   if (src_format->extradata)
   {
      VC_CONTAINER_STATUS_T status;
      uint32_t extradata_size = src_format->extradata_size;

      status = vc_container_track_allocate_extradata(p_ctx, track, extradata_size);
      if (status != VC_CONTAINER_SUCCESS)
         return status;

      memcpy(dst_format->extradata, src_format->extradata, extradata_size);
      dst_format->extradata_size = extradata_size;
   }

   track->is_enabled = reader->tracks[0]->is_enabled;

   return VC_CONTAINER_SUCCESS;
}