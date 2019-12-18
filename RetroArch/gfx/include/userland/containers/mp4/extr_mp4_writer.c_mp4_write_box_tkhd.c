#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_19__ {TYPE_4__* format; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_T ;
struct TYPE_20__ {int duration; TYPE_5__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {size_t current_track; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_18__ {scalar_t__ es_type; TYPE_3__* type; } ;
struct TYPE_16__ {int width; int height; int par_den; scalar_t__ par_num; } ;
struct TYPE_17__ {TYPE_2__ video; } ;
struct TYPE_15__ {TYPE_7__* module; } ;

/* Variables and functions */
 unsigned int MP4_64BITS_TIME ; 
 int MP4_TIMESCALE ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_6__*) ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_SUBPICTURE ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  WRITE_U16 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U24 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U64 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_6__*,unsigned int,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_tkhd( VC_CONTAINER_T *p_ctx )
{
   static uint32_t matrix[] = { 0x10000,0,0,0,0x10000,0,0,0,0x40000000 };
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[module->current_track];
   unsigned int version = MP4_64BITS_TIME;
   uint32_t i, width = 0, height = 0;

   WRITE_U8(p_ctx,  version, "version");
   WRITE_U24(p_ctx, 0x7, "flags"); /* track enabled */

   if(version)
   {
      WRITE_U64(p_ctx, 0, "creation_time");
      WRITE_U64(p_ctx, 0, "modification_time");
      WRITE_U32(p_ctx, module->current_track + 1, "track_ID");
      WRITE_U32(p_ctx, 0, "reserved");
      WRITE_U64(p_ctx, p_ctx->duration * MP4_TIMESCALE / 1000000, "duration");
   }
   else
   {
      WRITE_U32(p_ctx, 0, "creation_time");
      WRITE_U32(p_ctx, 0, "modification_time");
      WRITE_U32(p_ctx, module->current_track + 1, "track_ID");
      WRITE_U32(p_ctx, 0, "reserved");
      WRITE_U32(p_ctx, p_ctx->duration * MP4_TIMESCALE / 1000000, "duration");
   }

   for(i = 0; i < 2; i++)
      WRITE_U32(p_ctx, 0, "reserved");
   WRITE_U16(p_ctx, 0, "layer");
   WRITE_U16(p_ctx, 0, "alternate_group");
   WRITE_U16(p_ctx, track->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO ? 0x100 : 0, "volume");
   WRITE_U16(p_ctx, 0, "reserved");
   for(i = 0; i < 9; i++) /* unity matrix */
      WRITE_U32(p_ctx, matrix[i], "matrix");

   if(track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
   {
      width = track->format->type->video.width << 16;
      height = track->format->type->video.height << 16;
      if(track->format->type->video.par_num && track->format->type->video.par_den)
         width = width * (uint64_t)track->format->type->video.par_num /
            track->format->type->video.par_den;
   }
   else if(track->format->es_type == VC_CONTAINER_ES_TYPE_SUBPICTURE)
   {
      /* FIXME */
   }

   WRITE_U32(p_ctx, width, "width");
   WRITE_U32(p_ctx, height, "height");

   return STREAM_STATUS(p_ctx);
}