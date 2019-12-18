#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_20__ {TYPE_5__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {int pts; int dts; int flags; unsigned int frame_size; unsigned int size; int /*<<< orphan*/  data; int /*<<< orphan*/  buffer_size; scalar_t__ track; } ;
typedef  TYPE_7__ VC_CONTAINER_PACKET_T ;
struct TYPE_22__ {scalar_t__ status; unsigned int block_offset; int frame_header; int frames; unsigned int block_size; scalar_t__ yuv4mpeg2; } ;
typedef  TYPE_8__ VC_CONTAINER_MODULE_T ;
struct TYPE_19__ {TYPE_4__* format; } ;
struct TYPE_18__ {TYPE_3__* type; } ;
struct TYPE_16__ {int frame_rate_den; int frame_rate_num; } ;
struct TYPE_17__ {TYPE_2__ video; } ;
struct TYPE_15__ {TYPE_8__* module; } ;

/* Variables and functions */
 int INT64_C (int) ; 
 unsigned int MIN (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int READ_BYTES (TYPE_6__*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int SKIP_BYTES (TYPE_6__*,unsigned int) ; 
 scalar_t__ STREAM_STATUS (TYPE_6__*) ; 
 int VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int VC_CONTAINER_PACKET_FLAG_KEYFRAME ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int VC_CONTAINER_TIME_UNKNOWN ; 
 scalar_t__ read_yuv4mpeg2_frame_header (TYPE_6__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rawvideo_reader_read( VC_CONTAINER_T *ctx,
   VC_CONTAINER_PACKET_T *packet, uint32_t flags )
{
   VC_CONTAINER_MODULE_T *module = ctx->priv->module;
   unsigned int size;

   if (module->status != VC_CONTAINER_SUCCESS)
      return module->status;

   if (module->yuv4mpeg2 && !module->block_offset &&
         !module->frame_header)
   {
      module->status = read_yuv4mpeg2_frame_header(ctx);
      if (module->status != VC_CONTAINER_SUCCESS)
         return module->status;

      module->frame_header = true;
   }

   if (!module->block_offset)
      packet->pts = packet->dts = module->frames * INT64_C(1000000) *
         ctx->tracks[0]->format->type->video.frame_rate_den /
         ctx->tracks[0]->format->type->video.frame_rate_num;
   else
      packet->pts = packet->dts = VC_CONTAINER_TIME_UNKNOWN;
   packet->flags = VC_CONTAINER_PACKET_FLAG_FRAME_END |
      VC_CONTAINER_PACKET_FLAG_KEYFRAME;
   if (!module->block_offset)
      packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_START;
   packet->frame_size = module->block_size;
   packet->size = module->block_size - module->block_offset;
   packet->track = 0;

   if (flags & VC_CONTAINER_READ_FLAG_SKIP)
   {
      size = SKIP_BYTES(ctx, packet->size);
      module->block_offset = 0;
      module->frames++;
      module->frame_header = 0;
      module->status = STREAM_STATUS(ctx);
      return module->status;
   }

   if (flags & VC_CONTAINER_READ_FLAG_INFO)
      return VC_CONTAINER_SUCCESS;

   size = MIN(module->block_size - module->block_offset, packet->buffer_size);
   size = READ_BYTES(ctx, packet->data, size);
   module->block_offset += size;
   packet->size = size;

   if (module->block_offset == module->block_size)
   {
      module->block_offset = 0;
      module->frame_header = 0;
      module->frames++;
   }

   module->status = size ? VC_CONTAINER_SUCCESS : STREAM_STATUS(ctx);
   return module->status;
}