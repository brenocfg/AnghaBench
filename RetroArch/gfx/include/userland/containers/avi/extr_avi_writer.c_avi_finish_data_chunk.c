#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_END_CHUNK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SEEK (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SKIP_BYTES (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ STREAM_POSITION (int /*<<< orphan*/ *) ; 
 scalar_t__ STREAM_SEEKABLE (int /*<<< orphan*/ *) ; 
 scalar_t__ STREAM_STATUS (int /*<<< orphan*/ *) ; 
 scalar_t__ VC_CONTAINER_ERROR_FAILED ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_U32 (int /*<<< orphan*/ *,scalar_t__,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_finish_data_chunk( VC_CONTAINER_T *p_ctx, uint32_t chunk_size )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   if (chunk_size)
   {
      /* Rewrite the chunk size, this won't be efficient if it happens often */
      if (STREAM_SEEKABLE(p_ctx))
      {
         SEEK(p_ctx, STREAM_POSITION(p_ctx) - chunk_size - 4);
         WRITE_U32(p_ctx, chunk_size, "Chunk Size");
         SKIP_BYTES(p_ctx, chunk_size);
      }
      else
      {
         LOG_DEBUG(p_ctx, "warning, can't rewrite chunk size, data will be malformed");
         status = VC_CONTAINER_ERROR_FAILED;
      }
   }

   AVI_END_CHUNK(p_ctx);

   if (status != VC_CONTAINER_SUCCESS) status = STREAM_STATUS(p_ctx);

   return status;
}