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
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;
struct TYPE_15__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_16__ {int dts; int pts; scalar_t__ size; scalar_t__ buffer_size; scalar_t__ flags; int /*<<< orphan*/  data; scalar_t__ track; } ;
typedef  TYPE_5__ VC_CONTAINER_PACKET_T ;
struct TYPE_17__ {int position; scalar_t__ frame_data_left; scalar_t__ block_size; scalar_t__ data_size; } ;
typedef  TYPE_6__ VC_CONTAINER_MODULE_T ;
struct TYPE_14__ {TYPE_2__* format; } ;
struct TYPE_13__ {int bitrate; } ;
struct TYPE_12__ {TYPE_6__* module; } ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ READ_BYTES (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SKIP_BYTES (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_4__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 scalar_t__ VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 scalar_t__ VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 scalar_t__ VC_CONTAINER_READ_FLAG_INFO ; 
 scalar_t__ VC_CONTAINER_READ_FLAG_SKIP ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T wav_reader_read( VC_CONTAINER_T *p_ctx,
                                              VC_CONTAINER_PACKET_T *p_packet, uint32_t flags )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   uint32_t packet_flags = 0, size, data_size;
   int64_t pts;

   pts = module->position * 8000000 / p_ctx->tracks[0]->format->bitrate;
   data_size = module->frame_data_left;
   if(!data_size)
   {
      data_size = module->block_size;
      packet_flags |= VC_CONTAINER_PACKET_FLAG_FRAME_START;
   }
   module->frame_data_left = 0;

   if(module->position + data_size > module->data_size)
      data_size = module->data_size - module->position;
   if(data_size == 0) return VC_CONTAINER_ERROR_EOS;

   if((flags & VC_CONTAINER_READ_FLAG_SKIP) && !(flags & VC_CONTAINER_READ_FLAG_INFO)) /* Skip packet */
   {
      size = SKIP_BYTES(p_ctx, data_size);
      module->frame_data_left = data_size - size;
      module->position += size;
      return STREAM_STATUS(p_ctx);
   }

   p_packet->flags = packet_flags;
   p_packet->dts = p_packet->pts = pts;
   p_packet->track = 0;

   if(flags & VC_CONTAINER_READ_FLAG_SKIP)
   {
      size = SKIP_BYTES(p_ctx, data_size);
      module->frame_data_left = data_size - size;
      if(!module->frame_data_left) p_packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_END;
      module->position += size;
      p_packet->size += size;
      return STREAM_STATUS(p_ctx);
   }

   if(flags & VC_CONTAINER_READ_FLAG_INFO)
      return VC_CONTAINER_SUCCESS;

   size = MIN(data_size, p_packet->buffer_size - p_packet->size);
   size = READ_BYTES(p_ctx, p_packet->data, size);
   module->frame_data_left = data_size - size;
   if(!module->frame_data_left) p_packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_END;
   module->position += size;
   p_packet->size += size;

   return STREAM_STATUS(p_ctx);
}