#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {unsigned int tracks_num; TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_9__ {TYPE_5__* io; } ;
struct TYPE_11__ {TYPE_2__ temp_io; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_12__ {int /*<<< orphan*/  status; } ;
struct TYPE_8__ {TYPE_4__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FAILED ; 
 int /*<<< orphan*/  vc_container_io_read_be_uint32 (TYPE_5__*) ; 
 unsigned int vc_container_io_read_uint8 (TYPE_5__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_read_index_entry( VC_CONTAINER_T *p_ctx,
   unsigned int *p_track_num, uint32_t *p_chunk_size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   uint32_t chunk_size;
   uint8_t track_num;

   track_num = vc_container_io_read_uint8(module->temp_io.io);
   chunk_size = vc_container_io_read_be_uint32(module->temp_io.io);

   /* This shouldn't really happen if the temporary I/O is reliable */
   if (track_num >= p_ctx->tracks_num) return VC_CONTAINER_ERROR_FAILED;

   *p_track_num = track_num;
   *p_chunk_size = chunk_size;

   return module->temp_io.io->status;
}