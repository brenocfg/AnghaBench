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
typedef  int uint32_t ;
struct TYPE_11__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {unsigned int size; int /*<<< orphan*/  data; int /*<<< orphan*/  buffer_size; scalar_t__ flags; scalar_t__ track; scalar_t__ pts; scalar_t__ dts; } ;
typedef  TYPE_3__ VC_CONTAINER_PACKET_T ;
struct TYPE_13__ {scalar_t__ status; unsigned int block_size; unsigned int default_block_size; scalar_t__ init; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_10__ {TYPE_4__* module; } ;

/* Variables and functions */
 unsigned int MIN (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int READ_BYTES (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int SKIP_BYTES (TYPE_2__*,unsigned int) ; 
 scalar_t__ STREAM_STATUS (TYPE_2__*) ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ VC_CONTAINER_TIME_UNKNOWN ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T binary_reader_read( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *packet, uint32_t flags )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   unsigned int size;

   if(module->status != VC_CONTAINER_SUCCESS)
      return module->status;

   if(!module->block_size)
   {
      module->block_size = module->default_block_size;
      module->init = 0;
   }

   packet->size = module->block_size;
   packet->dts = packet->pts = VC_CONTAINER_TIME_UNKNOWN;
   if(module->init) packet->dts = packet->pts = 0;
   packet->track = 0;
   packet->flags = 0;

   if(flags & VC_CONTAINER_READ_FLAG_SKIP)
   {
      size = SKIP_BYTES(p_ctx, module->block_size);
      module->block_size -= size;
      module->status = STREAM_STATUS(p_ctx);
      return module->status;
   }

   if(flags & VC_CONTAINER_READ_FLAG_INFO)
      return VC_CONTAINER_SUCCESS;

   size = MIN(module->block_size, packet->buffer_size);
   size = READ_BYTES(p_ctx, packet->data, size);
   module->block_size -= size;
   packet->size = size;

   module->status = size ? VC_CONTAINER_SUCCESS : STREAM_STATUS(p_ctx);
   return module->status;
}