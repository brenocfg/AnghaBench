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
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_6__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {unsigned int current_track; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_18__ {TYPE_2__* format; } ;
struct TYPE_15__ {scalar_t__ es_type; int extradata_size; } ;
struct TYPE_14__ {TYPE_4__* module; } ;
typedef  int /*<<< orphan*/  GUID_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_GUID (TYPE_3__*,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  WRITE_U16 (TYPE_3__*,unsigned int,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_3__*,unsigned int,char*) ; 
 int /*<<< orphan*/  WRITE_U64 (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  const asf_guid_error_correction ; 
 int /*<<< orphan*/  asf_guid_stream_type_audio ; 
 int /*<<< orphan*/  asf_guid_stream_type_video ; 
 int /*<<< orphan*/  asf_write_bitmapinfoheader (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  asf_write_waveformatex (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  guid_null ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_write_object_stream_properties( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   unsigned int track = module->current_track, ts_size = 0;
   const GUID_T *p_guid = &guid_null;

   if(p_ctx->tracks[track]->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
   {
      p_guid = &asf_guid_stream_type_video;
      ts_size = 11 + 40 + p_ctx->tracks[track]->format->extradata_size;
   }
   else if(p_ctx->tracks[track]->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO)
   {
      p_guid = &asf_guid_stream_type_audio;
      ts_size = 18 + p_ctx->tracks[track]->format->extradata_size;
   }

   WRITE_GUID(p_ctx, p_guid, "Stream Type");
   WRITE_GUID(p_ctx, &asf_guid_error_correction, "Error Correction Type");
   WRITE_U64(p_ctx, 0, "Time Offset");
   WRITE_U32(p_ctx, ts_size, "Type-Specific Data Length");
   WRITE_U32(p_ctx, 0, "Error Correction Data Length");
   WRITE_U16(p_ctx, track + 1, "Flags");
   WRITE_U32(p_ctx, 0, "Reserved");

   /* Type-Specific Data */
   if(ts_size)
   {
      if(p_ctx->tracks[track]->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
         status = asf_write_bitmapinfoheader( p_ctx, p_ctx->tracks[track]);
      else if(p_ctx->tracks[track]->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO)
         status = asf_write_waveformatex( p_ctx, p_ctx->tracks[track]);
   }

   /* Error Correction Data */

   return status;
}