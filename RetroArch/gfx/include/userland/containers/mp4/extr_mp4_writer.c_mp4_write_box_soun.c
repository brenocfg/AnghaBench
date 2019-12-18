#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_4__* format; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_T ;
struct TYPE_22__ {TYPE_5__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_23__ {size_t current_track; scalar_t__ brand; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_20__ {int codec; TYPE_3__* type; } ;
struct TYPE_18__ {unsigned int channels; int sample_rate; } ;
struct TYPE_19__ {TYPE_2__ audio; } ;
struct TYPE_17__ {TYPE_7__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BOX_TYPE_ESDS ; 
 scalar_t__ MP4_BRAND_QT ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_6__*) ; 
#define  VC_CONTAINER_CODEC_AMRNB 133 
#define  VC_CONTAINER_CODEC_AMRWB 132 
#define  VC_CONTAINER_CODEC_AMRWBP 131 
#define  VC_CONTAINER_CODEC_EVRC 130 
#define  VC_CONTAINER_CODEC_MP4A 129 
#define  VC_CONTAINER_CODEC_MPGA 128 
 int /*<<< orphan*/  WRITE_U16 (TYPE_6__*,unsigned int,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp4_write_box (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4_write_box_soun_damr (TYPE_6__*) ; 
 int /*<<< orphan*/  mp4_write_box_soun_dawp (TYPE_6__*) ; 
 int /*<<< orphan*/  mp4_write_box_soun_devc (TYPE_6__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_soun( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[module->current_track];
   unsigned int i, version = 0;

   for(i = 0; i < 6; i++) WRITE_U8(p_ctx, 0, "reserved");
   WRITE_U16(p_ctx, 1, "data_reference_index");

   if(module->brand == MP4_BRAND_QT)
   {
      if(track->format->codec == VC_CONTAINER_CODEC_MP4A) version = 1;
      WRITE_U16(p_ctx, version, "version");
      WRITE_U16(p_ctx, 0, "revision_level");
      WRITE_U32(p_ctx, 0, "vendor");
   }
   else
   {
      for(i = 0; i < 2; i++) WRITE_U32(p_ctx, 0, "reserved");
   }

   WRITE_U16(p_ctx, track->format->type->audio.channels, "channelcount");
   WRITE_U16(p_ctx, 0, "samplesize");
   WRITE_U16(p_ctx, 0, "pre_defined");
   WRITE_U16(p_ctx, 0, "reserved");
   WRITE_U32(p_ctx, track->format->type->audio.sample_rate << 16, "samplerate");

   if(module->brand == MP4_BRAND_QT && version == 1) /* FIXME */
   {
      WRITE_U32(p_ctx, 1024, "samples_per_packet");
      WRITE_U32(p_ctx, 1536, "bytes_per_packet");
      WRITE_U32(p_ctx, 2, "bytes_per_frame");
      WRITE_U32(p_ctx, 2, "bytes_per_sample");
   }

   switch(track->format->codec)
   {
   case VC_CONTAINER_CODEC_AMRNB:
   case VC_CONTAINER_CODEC_AMRWB:
      return mp4_write_box_soun_damr(p_ctx);
   case VC_CONTAINER_CODEC_AMRWBP:
      return mp4_write_box_soun_dawp(p_ctx);
   case VC_CONTAINER_CODEC_EVRC:
      return mp4_write_box_soun_devc(p_ctx);
   case VC_CONTAINER_CODEC_MP4A:
   case VC_CONTAINER_CODEC_MPGA:
      return mp4_write_box(p_ctx, MP4_BOX_TYPE_ESDS);
   default: break;
   }

   return STREAM_STATUS(p_ctx);
}