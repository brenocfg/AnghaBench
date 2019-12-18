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
struct TYPE_23__ {size_t current_track; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_20__ {int codec; TYPE_3__* type; } ;
struct TYPE_18__ {int width; int height; } ;
struct TYPE_19__ {TYPE_2__ video; } ;
struct TYPE_17__ {TYPE_7__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BOX_TYPE_ESDS ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_6__*) ; 
#define  VC_CONTAINER_CODEC_H263 130 
#define  VC_CONTAINER_CODEC_H264 129 
#define  VC_CONTAINER_CODEC_MP4V 128 
 int /*<<< orphan*/  WRITE_U16 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _WRITE_U8 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4_write_box (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4_write_box_vide_avcC (TYPE_6__*) ; 
 int /*<<< orphan*/  mp4_write_box_vide_d263 (TYPE_6__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_vide( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[module->current_track];
   unsigned int i;

   for(i = 0; i < 6; i++) WRITE_U8(p_ctx, 0, "reserved");
   WRITE_U16(p_ctx, 1, "data_reference_index");

   WRITE_U16(p_ctx, 0, "pre_defined");
   WRITE_U16(p_ctx, 0, "reserved");
   for(i = 0; i < 3; i++) WRITE_U32(p_ctx, 0, "pre_defined");
   WRITE_U16(p_ctx, track->format->type->video.width, "width");
   WRITE_U16(p_ctx, track->format->type->video.height, "height");
   WRITE_U32(p_ctx, 0x480000, "horizresolution"); /* 72 dpi */
   WRITE_U32(p_ctx, 0x480000, "vertresolution"); /* 72 dpi */
   WRITE_U32(p_ctx, 0, "reserved");
   WRITE_U16(p_ctx, 1, "frame_count");
   for(i = 0; i < 32; i++) _WRITE_U8(p_ctx, 0);
   WRITE_U16(p_ctx, 0x18, "depth");
   WRITE_U16(p_ctx, -1, "pre_defined");

   switch(track->format->codec)
   {
   case VC_CONTAINER_CODEC_H264: return mp4_write_box_vide_avcC(p_ctx);
   case VC_CONTAINER_CODEC_H263: return mp4_write_box_vide_d263(p_ctx);
   case VC_CONTAINER_CODEC_MP4V: return mp4_write_box(p_ctx, MP4_BOX_TYPE_ESDS);
   default: break;
   }

   return STREAM_STATUS(p_ctx);
}