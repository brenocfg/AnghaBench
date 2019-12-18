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
 int AVI_TWOCC (char,char) ; 
 int PEEK_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ READ_FOURCC (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ READ_U32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SKIP_FOURCC (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ VC_FOURCC (char,char,char,char) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_find_next_data_chunk(VC_CONTAINER_T *p_ctx, uint32_t *id, uint32_t *size)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_FOURCC_T chunk_id;
   uint32_t chunk_size = 0;
   uint32_t peek_buf[1];

   do
   {
      chunk_id = READ_FOURCC(p_ctx, "Chunk ID");
      chunk_size = READ_U32(p_ctx, "Chunk size");
      if((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS)
         break;

      /* Check if this is a 'rec ' or a 'movi' LIST instead of a plain data chunk */
      if(chunk_id == VC_FOURCC('L','I','S','T'))
      {
         if (PEEK_BYTES(p_ctx, (uint8_t*)peek_buf, 4) != 4)
            return VC_CONTAINER_ERROR_EOS;
         if (peek_buf[0] == VC_FOURCC('r','e','c',' '))
            SKIP_FOURCC(p_ctx, "rec ");
         else if (peek_buf[0] == VC_FOURCC('m','o','v','i'))
            SKIP_FOURCC(p_ctx, "movi");
         else
            AVI_SKIP_CHUNK(p_ctx, chunk_size); /* Not interested in this LIST chunk, skip it. */
         continue;
      }

      /* Check if this is a 'AVIX' RIFF header instead of a data chunk */
      if(chunk_id == VC_FOURCC('R','I','F','F'))
      {
         if (PEEK_BYTES(p_ctx, (uint8_t*)peek_buf, 4) != 4)
            return VC_CONTAINER_ERROR_EOS;
         if (peek_buf[0] == VC_FOURCC('A','V','I','X'))
            SKIP_FOURCC(p_ctx, "AVIX");
         else
            AVI_SKIP_CHUNK(p_ctx, chunk_size); /* Not interested in this RIFF header, skip it. */
         continue;
      }

      /* We treat only db/dc/dd or wb chunks as data */
      if((uint32_t)chunk_id >> 16 == AVI_TWOCC('d','c') ||
         (uint32_t)chunk_id >> 16 == AVI_TWOCC('d','b') ||
         (uint32_t)chunk_id >> 16 == AVI_TWOCC('d','d') ||
         (uint32_t)chunk_id >> 16 == AVI_TWOCC('w','b'))
      {
         *id = chunk_id;
         *size = chunk_size;
         break;
      }

      /* Need to exit if a zero sized chunk encountered so we don't loop forever. */
      if(chunk_size == 0 && chunk_id == 0) return VC_CONTAINER_ERROR_EOS;

      /* Not interested in this chunk, skip it */
      AVI_SKIP_CHUNK(p_ctx, chunk_size);
   } while ((status = STREAM_STATUS(p_ctx)) == VC_CONTAINER_SUCCESS);

   return status;
}