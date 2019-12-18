#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_11__ {TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_10__ {TYPE_5__* io; } ;
struct TYPE_12__ {scalar_t__ index_status; TYPE_2__ temp_io; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_13__ {scalar_t__ status; } ;
struct TYPE_9__ {TYPE_4__* module; } ;

/* Variables and functions */
 int AVI_INDEX_DELTAFRAME ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_3__*,char*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  vc_container_io_write_be_uint32 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  vc_container_io_write_uint8 (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_write_index_entry( VC_CONTAINER_T *p_ctx, uint8_t track_num,
   uint32_t chunk_size, int keyframe )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   uint32_t deltaframe = keyframe ? 0 : AVI_INDEX_DELTAFRAME;

   vc_container_io_write_uint8(module->temp_io.io, track_num);
   vc_container_io_write_be_uint32(module->temp_io.io, chunk_size | deltaframe);

   if (module->temp_io.io->status != VC_CONTAINER_SUCCESS)
   {
      module->index_status = module->temp_io.io->status;
      LOG_DEBUG(p_ctx, "warning, couldn't store index data, index data will be incorrect");
   }

   return module->temp_io.io->status;
}