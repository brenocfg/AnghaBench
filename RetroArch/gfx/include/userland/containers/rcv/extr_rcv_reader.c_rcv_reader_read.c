#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  long long int64_t ;
struct TYPE_14__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_15__ {unsigned int size; long long dts; long long pts; int /*<<< orphan*/  flags; TYPE_11__* data; int /*<<< orphan*/  buffer_size; scalar_t__ track; } ;
typedef  TYPE_3__ VC_CONTAINER_PACKET_T ;
struct TYPE_12__ {long long timestamp; unsigned int framesize; scalar_t__ keyframe; } ;
struct TYPE_16__ {int mid_frame; scalar_t__ frame_read; TYPE_11__ frame; scalar_t__ index; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_13__ {TYPE_4__* module; } ;
typedef  int /*<<< orphan*/  RCV_FRAME_HEADER_T ;

/* Variables and functions */
 unsigned int MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int READ_BYTES (TYPE_2__*,TYPE_11__*,unsigned int) ; 
 unsigned int SKIP_BYTES (TYPE_2__*,scalar_t__) ; 
 long long STREAM_POSITION (TYPE_2__*) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_KEYFRAME ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  vc_container_index_add (scalar_t__,long long,long long) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rcv_reader_read( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *packet, uint32_t flags )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   unsigned int size;

   if(!module->mid_frame)
   {
      /* Save the current position for updating the indexer */
      int64_t position = STREAM_POSITION(p_ctx);

      if(READ_BYTES(p_ctx, &module->frame, sizeof(RCV_FRAME_HEADER_T)) != sizeof(RCV_FRAME_HEADER_T))
         return VC_CONTAINER_ERROR_EOS;
      module->mid_frame = 1;
      module->frame_read = 0;

      if(module->index && module->frame.keyframe)
         vc_container_index_add(module->index, (int64_t)module->frame.timestamp * 1000LL, position);
   }

   packet->size = module->frame.framesize;
   packet->dts = packet->pts = module->frame.timestamp * 1000LL;
   packet->track = 0;
   packet->flags = 0;
   if(module->frame_read == 0)
      packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_START;
   if(module->frame.keyframe)
      packet->flags |= VC_CONTAINER_PACKET_FLAG_KEYFRAME;

   if(flags & VC_CONTAINER_READ_FLAG_SKIP)
   {
      size = SKIP_BYTES(p_ctx, module->frame.framesize - module->frame_read);
      if((module->frame_read += size) == module->frame.framesize)
      {
         module->frame_read = 0;
         module->mid_frame = 0;
      }
      return STREAM_STATUS(p_ctx);
   }

   if(flags & VC_CONTAINER_READ_FLAG_INFO)
      return VC_CONTAINER_SUCCESS;

   size = MIN(module->frame.framesize - module->frame_read, packet->buffer_size);
   size = READ_BYTES(p_ctx, packet->data, size);
   if((module->frame_read += size) == module->frame.framesize)
   {
      module->frame_read = 0;
      module->mid_frame = 0;
      packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_END;
   }
   packet->size = size;

   return size ? VC_CONTAINER_SUCCESS : STREAM_STATUS(p_ctx);
}