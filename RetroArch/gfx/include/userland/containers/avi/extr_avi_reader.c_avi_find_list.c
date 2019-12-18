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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  scalar_t__ VC_CONTAINER_FOURCC_T ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_SKIP_CHUNK (int /*<<< orphan*/ *,scalar_t__) ; 
 int PEEK_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ READ_FOURCC (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ READ_U32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ VC_FOURCC (char,char,char,char) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_find_list(VC_CONTAINER_T *p_ctx, VC_CONTAINER_FOURCC_T fourcc, uint32_t *size)
{
   VC_CONTAINER_STATUS_T status;
   VC_CONTAINER_FOURCC_T chunk_id;
   uint32_t chunk_size;
   uint32_t peek_buf[1];

   do {
      chunk_id = READ_FOURCC(p_ctx, "Chunk ID");
      chunk_size = READ_U32(p_ctx, "Chunk size");
      if((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS) return status;

      if(chunk_id == VC_FOURCC('L','I','S','T'))
      {
         if (PEEK_BYTES(p_ctx, (uint8_t*)peek_buf, 4) != 4)
            return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
         if (peek_buf[0] == fourcc)
         {
            *size = chunk_size;
            return VC_CONTAINER_SUCCESS;
         }
      }
      /* Not interested in this chunk, skip it. */
      AVI_SKIP_CHUNK(p_ctx, chunk_size);
   } while((status = STREAM_STATUS(p_ctx)) == VC_CONTAINER_SUCCESS);

   return status; /* list not found */
}