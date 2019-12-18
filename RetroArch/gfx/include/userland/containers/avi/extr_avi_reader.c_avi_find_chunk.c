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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  scalar_t__ VC_CONTAINER_FOURCC_T ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_SKIP_CHUNK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ READ_FOURCC (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  READ_U32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_find_chunk(VC_CONTAINER_T *p_ctx, VC_CONTAINER_FOURCC_T id, uint32_t *size)
{
   VC_CONTAINER_STATUS_T status;
   VC_CONTAINER_FOURCC_T chunk_id;
   uint32_t chunk_size;

   do {
      chunk_id = READ_FOURCC(p_ctx, "Chunk ID");
      chunk_size = READ_U32(p_ctx, "Chunk size");
      if((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS) return status;

      if(chunk_id == id)
      {
         *size = chunk_size;
         return VC_CONTAINER_SUCCESS;
      }
      /* Not interested in this chunk, skip it. */
      AVI_SKIP_CHUNK(p_ctx, chunk_size);
   } while((status = STREAM_STATUS(p_ctx)) == VC_CONTAINER_SUCCESS);

   return status; /* chunk not found */
}