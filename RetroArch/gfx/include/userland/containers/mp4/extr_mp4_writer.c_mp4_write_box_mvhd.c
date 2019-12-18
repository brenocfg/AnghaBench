#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_13__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_TRACK_T ;
struct TYPE_14__ {scalar_t__ last_pts; scalar_t__ first_pts; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_15__ {scalar_t__ duration; unsigned int tracks_num; TYPE_2__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {TYPE_3__* module; } ;

/* Variables and functions */
 unsigned int MP4_64BITS_TIME ; 
 int MP4_TIMESCALE ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_4__*) ; 
 int /*<<< orphan*/  WRITE_U16 (TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U24 (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U64 (TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_4__*,unsigned int,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_mvhd( VC_CONTAINER_T *p_ctx )
{
   static uint32_t matrix[] = { 0x10000,0,0,0,0x10000,0,0,0,0x40000000 };
   unsigned int version = MP4_64BITS_TIME;
   unsigned int i;

   WRITE_U8(p_ctx,  version, "version");
   WRITE_U24(p_ctx, 0, "flags");

   /**/
   p_ctx->duration = 0;
   for(i = 0; i < p_ctx->tracks_num; i++)
   {
      VC_CONTAINER_TRACK_T *track = p_ctx->tracks[i];
      VC_CONTAINER_TRACK_MODULE_T *track_module = track->priv->module;
      int64_t track_duration = track_module->last_pts - track_module->first_pts;
      if(track_duration > p_ctx->duration)
         p_ctx->duration = track_duration;
   }

   if(version)
   {
      WRITE_U64(p_ctx, 0, "creation_time");
      WRITE_U64(p_ctx, 0, "modification_time");
      WRITE_U32(p_ctx, MP4_TIMESCALE, "timescale");
      WRITE_U64(p_ctx, p_ctx->duration * MP4_TIMESCALE / 1000000, "duration");
   }
   else
   {
      WRITE_U32(p_ctx, 0, "creation_time");
      WRITE_U32(p_ctx, 0, "modification_time");
      WRITE_U32(p_ctx, MP4_TIMESCALE, "timescale");
      WRITE_U32(p_ctx, p_ctx->duration * MP4_TIMESCALE / 1000000, "duration");
   }

   WRITE_U32(p_ctx, 0x10000, "rate"); /* 1.0 */
   WRITE_U16(p_ctx, 0x100, "volume"); /* full volume */
   WRITE_U16(p_ctx, 0, "reserved");
   for(i = 0; i < 2; i++)
      WRITE_U32(p_ctx, 0, "reserved");
   for(i = 0; i < 9; i++) /* unity matrix */
      WRITE_U32(p_ctx, matrix[i], "matrix");
   for(i = 0; i < 6; i++)
      WRITE_U32(p_ctx, 0, "pre_defined");
   WRITE_U32(p_ctx, p_ctx->tracks_num + 1, "next_track_ID");

   return STREAM_STATUS(p_ctx);
}