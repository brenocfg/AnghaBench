#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* format; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
struct TYPE_11__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {size_t current_track; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_9__ {scalar_t__ es_type; } ;
struct TYPE_8__ {TYPE_5__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BOX_TYPE_CO64 ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_CTTS ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_STCO ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_STSC ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_STSD ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_STSS ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_STSZ ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_STTS ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mp4_write_box (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_stbl( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[module->current_track];

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_STSD);
   if(status != VC_CONTAINER_SUCCESS) return status;

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_STTS);
   if(status != VC_CONTAINER_SUCCESS) return status;

   if( 0 && track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
   {
      status = mp4_write_box(p_ctx, MP4_BOX_TYPE_CTTS);
      if(status != VC_CONTAINER_SUCCESS) return status;
   }

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_STSC);
   if(status != VC_CONTAINER_SUCCESS) return status;

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_STSZ);
   if(status != VC_CONTAINER_SUCCESS) return status;

   if(1)
      status = mp4_write_box(p_ctx, MP4_BOX_TYPE_STCO);
   else
      status = mp4_write_box(p_ctx, MP4_BOX_TYPE_CO64);

   if(track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
   {
      status = mp4_write_box(p_ctx, MP4_BOX_TYPE_STSS);
      if(status != VC_CONTAINER_SUCCESS) return status;
   }

   return status;
}