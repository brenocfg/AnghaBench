#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_13__ {TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_14__ {int track; int /*<<< orphan*/  flags; scalar_t__ dts; scalar_t__ pts; scalar_t__ size; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
struct TYPE_12__ {TYPE_6__* io; } ;
struct TYPE_15__ {TYPE_2__ temp; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_16__ {int /*<<< orphan*/  status; } ;
struct TYPE_11__ {TYPE_5__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_KEYFRAME ; 
 scalar_t__ vc_container_io_read_be_uint24 (TYPE_6__*) ; 
 scalar_t__ vc_container_io_read_be_uint32 (TYPE_6__*) ; 
 int vc_container_io_read_uint8 (TYPE_6__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_writer_read_sample_from_temp( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *packet)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;

   packet->size = vc_container_io_read_be_uint32(module->temp.io);
   packet->dts += (int32_t)vc_container_io_read_be_uint32(module->temp.io);
   packet->pts = packet->dts + vc_container_io_read_be_uint24(module->temp.io);
   packet->track = vc_container_io_read_uint8(module->temp.io);
   packet->flags = (packet->track & 0x80) ? VC_CONTAINER_PACKET_FLAG_KEYFRAME : 0;
   packet->track &= 0x7F;
   return module->temp.io->status;
}