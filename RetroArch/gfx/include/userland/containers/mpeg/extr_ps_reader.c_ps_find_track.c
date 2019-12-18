#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
struct TYPE_13__ {unsigned int tracks_num; TYPE_3__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
struct TYPE_11__ {TYPE_1__* module; } ;
struct TYPE_10__ {scalar_t__ stream_id; scalar_t__ substream_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_4__*,char*,scalar_t__) ; 
 unsigned int PS_TRACKS_MAX ; 
 TYPE_3__* vc_container_allocate_track (TYPE_4__*,int) ; 

__attribute__((used)) static VC_CONTAINER_TRACK_T *ps_find_track( VC_CONTAINER_T *ctx, uint32_t stream_id,
   uint32_t substream_id, bool b_create )
{
   VC_CONTAINER_TRACK_T *track = 0;
   unsigned int i;

   for(i = 0; i < ctx->tracks_num; i++)
      if(ctx->tracks[i]->priv->module->stream_id == stream_id &&
         ctx->tracks[i]->priv->module->substream_id == substream_id) break;

   if(i < ctx->tracks_num) /* We found it */
      track = ctx->tracks[i];

   if(!track && b_create && i < PS_TRACKS_MAX)
   {
      /* Allocate and initialise a new track */
      ctx->tracks[i] = track =
         vc_container_allocate_track(ctx, sizeof(*ctx->tracks[0]->priv->module));
      if(track)
      {
         track->priv->module->stream_id = stream_id;
         track->priv->module->substream_id = substream_id;
         ctx->tracks_num++;
      }
   }

   if(!track && b_create)
      LOG_DEBUG(ctx, "could not create track for stream id: %i", stream_id);

   return track;
}