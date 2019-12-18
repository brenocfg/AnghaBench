#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_15__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_16__ {scalar_t__ size; scalar_t__ frame_size; } ;
typedef  TYPE_3__ VC_CONTAINER_PACKET_T ;
struct TYPE_17__ {int /*<<< orphan*/  null_io; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_14__ {TYPE_4__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_END_CHUNK (TYPE_2__*) ; 
 scalar_t__ AVI_INDEX_ENTRY_SIZE ; 
 scalar_t__ AVI_STD_INDEX_ENTRY_SIZE ; 
 scalar_t__ STREAM_POSITION (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_BYTES (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ avi_write_legacy_index_data (TYPE_2__*) ; 
 scalar_t__ avi_write_standard_index_data (TYPE_2__*) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_container_writer_extraio_disable (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int vc_container_writer_extraio_enable (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t avi_calculate_file_size( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *p_packet )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   int64_t filesize = 0;
   int refcount;

   /* Start from current file position */
   filesize = STREAM_POSITION(p_ctx);

   refcount = vc_container_writer_extraio_enable(p_ctx, &module->null_io);
   vc_container_assert(refcount == 0); /* Although perfectly harmless, we should
                                          not be called with the null i/o enabled. */
   VC_CONTAINER_PARAM_UNUSED(refcount);

   do {
      /* If we know what the final size of the chunk is going to be,
         we can use that here to avoid writing a partial final packet */
      WRITE_BYTES(p_ctx, NULL, p_packet->frame_size ? p_packet->frame_size : p_packet->size);
      AVI_END_CHUNK(p_ctx);

      /* Index entries for the chunk */
      WRITE_BYTES(p_ctx, NULL, AVI_INDEX_ENTRY_SIZE + AVI_STD_INDEX_ENTRY_SIZE);

      /* Current standard index data */
      if (avi_write_standard_index_data(p_ctx) != VC_CONTAINER_SUCCESS) break;

      /* Current legacy index data */
      status = avi_write_legacy_index_data(p_ctx);
      if (status != VC_CONTAINER_SUCCESS) break;
   } while(0);

   filesize += STREAM_POSITION(p_ctx);

   vc_container_writer_extraio_disable(p_ctx, &module->null_io);

   return filesize;
}