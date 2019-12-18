#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_T ;
struct TYPE_16__ {unsigned int tracks_num; TYPE_4__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
struct TYPE_17__ {unsigned int* stream_number_to_index; } ;
typedef  TYPE_6__ VC_CONTAINER_MODULE_T ;
struct TYPE_14__ {TYPE_2__* module; } ;
struct TYPE_13__ {unsigned int stream_id; } ;
struct TYPE_12__ {TYPE_6__* module; } ;

/* Variables and functions */
 unsigned int ASF_TRACKS_MAX ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_5__*,char*,unsigned int) ; 
 TYPE_4__* vc_container_allocate_track (TYPE_5__*,int) ; 

__attribute__((used)) static VC_CONTAINER_TRACK_T *asf_reader_find_track( VC_CONTAINER_T *p_ctx, unsigned int stream_id,
   bool b_create)
{
   VC_CONTAINER_TRACK_T *p_track = 0;
   VC_CONTAINER_MODULE_T * module = p_ctx->priv->module;
   unsigned int i;

   /* discard the key-frame flag */
   stream_id &= 0x7f;

   /* look to see if we have already allocated the stream */
   i = module->stream_number_to_index[stream_id];

   if(i < p_ctx->tracks_num) /* We found it */
      p_track = p_ctx->tracks[i];

   if(!p_track && b_create && p_ctx->tracks_num < ASF_TRACKS_MAX)
   {
      /* Allocate and initialise a new track */
      p_ctx->tracks[p_ctx->tracks_num] = p_track =
         vc_container_allocate_track(p_ctx, sizeof(*p_ctx->tracks[0]->priv->module));
      if(p_track)
      {
         /* store the stream ID */
         p_track->priv->module->stream_id = stream_id;

         /* Store the translation table value */
         module->stream_number_to_index[stream_id] = p_ctx->tracks_num;

         /* count the track */
         p_ctx->tracks_num++;
      }
   }

   if(!p_track && b_create)
      LOG_DEBUG(p_ctx, "could not create track for stream id: %i", stream_id);

   return p_track;
}