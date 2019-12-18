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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_18__ {unsigned int tracks_num; TYPE_5__* priv; TYPE_2__** tracks; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  scalar_t__ VC_CONTAINER_ES_TYPE_T ;
struct TYPE_17__ {TYPE_4__* module; } ;
struct TYPE_15__ {scalar_t__ index; } ;
struct TYPE_16__ {scalar_t__ video_track; TYPE_3__ state; } ;
struct TYPE_14__ {TYPE_1__* format; } ;
struct TYPE_13__ {scalar_t__ es_type; scalar_t__ codec; } ;

/* Variables and functions */
 int FLV_FLAG_DISCARD ; 
 int FLV_FLAG_KEYFRAME ; 
 int FLV_TAG_TYPE_AUDIO ; 
 int FLV_TAG_TYPE_METADATA ; 
 int FLV_TAG_TYPE_VIDEO ; 
 scalar_t__ STREAM_POSITION (TYPE_6__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_6__*) ; 
 int VC_CONTAINER_ERROR_CORRUPTED ; 
 int VC_CONTAINER_ERROR_EOS ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_UNKNOWN ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  flv_read_audiodata_header (TYPE_6__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flv_read_tag_header (TYPE_6__*,int*,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  flv_read_videodata_header (TYPE_6__*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  vc_container_index_add (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int flv_read_frame_header(VC_CONTAINER_T *p_ctx, int *p_prev_size,
   int *p_track, int *p_size, uint32_t *p_timestamp, int *p_flags,
   int b_extra_check)
{
   int64_t position = STREAM_POSITION(p_ctx);
   int type, size, flags = 0, frametype = 0;
   VC_CONTAINER_STATUS_T status;
   VC_CONTAINER_ES_TYPE_T es_type = VC_CONTAINER_ES_TYPE_UNKNOWN;
   unsigned int track = p_ctx->tracks_num;
   uint32_t codec = 0;

   status = flv_read_tag_header(p_ctx, p_prev_size, &type, &size, p_timestamp);
   if(status != VC_CONTAINER_SUCCESS) return status;

   if(STREAM_STATUS(p_ctx) != VC_CONTAINER_SUCCESS) return status;
   if(position == STREAM_POSITION(p_ctx)) return VC_CONTAINER_ERROR_EOS;
   if(type == 0) return VC_CONTAINER_ERROR_CORRUPTED;

   /* Sanity checking */
   if(b_extra_check && type != FLV_TAG_TYPE_AUDIO &&
      type != FLV_TAG_TYPE_VIDEO && type != FLV_TAG_TYPE_METADATA)
      return VC_CONTAINER_ERROR_CORRUPTED;

   /* We're only interested in audio / video */
   if((type != FLV_TAG_TYPE_AUDIO && type != FLV_TAG_TYPE_VIDEO) || !size)
   {
      flags |= FLV_FLAG_DISCARD;
      goto end;
   }

   if(type == FLV_TAG_TYPE_AUDIO)
   {
      flv_read_audiodata_header(p_ctx, &codec, 0, 0, 0);
      es_type = VC_CONTAINER_ES_TYPE_AUDIO;
   }
   else if(type == FLV_TAG_TYPE_VIDEO)
   {
      flv_read_videodata_header(p_ctx, &codec, &frametype);
      es_type = VC_CONTAINER_ES_TYPE_VIDEO;
   }
   size--;

   /* Find which track this belongs to */
   for(track = 0; track < p_ctx->tracks_num; track++)
      if(es_type == p_ctx->tracks[track]->format->es_type) break;
   if(track == p_ctx->tracks_num)
      flags |= FLV_FLAG_DISCARD;

   /* Sanity checking */
   if(b_extra_check && codec != p_ctx->tracks[track]->format->codec)
      return VC_CONTAINER_ERROR_CORRUPTED;

 end:
   // add to the index if we have one, and we're not discarding this frame.
   // also require that we either have no video track or this is a video frame marked as a key frame.
   if(p_ctx->priv->module->state.index && !(flags & FLV_FLAG_DISCARD) &&
      (p_ctx->priv->module->video_track < 0 || (es_type == VC_CONTAINER_ES_TYPE_VIDEO && (frametype & FLV_FLAG_KEYFRAME))))
      vc_container_index_add(p_ctx->priv->module->state.index, (int64_t) (*p_timestamp) * 1000LL, position);

   *p_flags = flags | frametype;
   *p_size = size;
   *p_track = track;
   return VC_CONTAINER_SUCCESS;
}