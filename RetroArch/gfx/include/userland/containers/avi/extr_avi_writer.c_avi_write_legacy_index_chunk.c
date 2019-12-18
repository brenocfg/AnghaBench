#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_19__ {TYPE_1__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_18__ {int /*<<< orphan*/  io; } ;
struct TYPE_17__ {scalar_t__ refcount; } ;
struct TYPE_20__ {TYPE_3__ temp_io; int /*<<< orphan*/  index_offset; TYPE_2__ null_io; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_16__ {TYPE_5__* module; } ;

/* Variables and functions */
 int AVIIF_KEYFRAME ; 
 int /*<<< orphan*/  AVI_END_CHUNK (TYPE_4__*) ; 
 int AVI_INDEX_DELTAFRAME ; 
 scalar_t__ AVI_INDEX_ENTRY_SIZE ; 
 int INT64_C (int) ; 
 int /*<<< orphan*/  STREAM_POSITION (TYPE_4__*) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_4__*) ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  WRITE_BYTES (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WRITE_FOURCC (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  avi_chunk_id_from_track_num (TYPE_4__*,int /*<<< orphan*/ *,unsigned int) ; 
 int avi_num_chunks (TYPE_4__*) ; 
 int /*<<< orphan*/  avi_read_index_entry (TYPE_4__*,unsigned int*,int*) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_container_io_seek (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_write_legacy_index_chunk( VC_CONTAINER_T *p_ctx, uint32_t index_size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status;
   uint32_t chunk_offset = 4;
   unsigned int track_num;

   vc_container_assert(8 + avi_num_chunks(p_ctx) * INT64_C(16) <= (int64_t)ULONG_MAX);

   if(module->null_io.refcount)
   {
      /* Assume that we're not actually writing the data,
         just want know the index size */
      WRITE_BYTES(p_ctx, NULL, 8 + avi_num_chunks(p_ctx) * (int64_t)AVI_INDEX_ENTRY_SIZE);
      return STREAM_STATUS(p_ctx);
   }

   module->index_offset = STREAM_POSITION(p_ctx);

   WRITE_FOURCC(p_ctx, VC_FOURCC('i','d','x','1'), "Chunk ID");
   WRITE_U32(p_ctx, index_size, "Chunk Size");

   /* Scan through all written entries, convert to appropriate index format */
   vc_container_io_seek(module->temp_io.io, INT64_C(0));

   while((status = STREAM_STATUS(p_ctx)) == VC_CONTAINER_SUCCESS)
   {
      VC_CONTAINER_FOURCC_T chunk_id;
      uint32_t chunk_size, flags;

      status = avi_read_index_entry(p_ctx, &track_num, &chunk_size);
      if (status != VC_CONTAINER_SUCCESS) break;

      avi_chunk_id_from_track_num(p_ctx, &chunk_id, track_num);
      flags = (chunk_size & AVI_INDEX_DELTAFRAME) ? 0 : AVIIF_KEYFRAME;
      chunk_size &= ~AVI_INDEX_DELTAFRAME;

      WRITE_FOURCC(p_ctx, chunk_id, "Chunk ID");
      WRITE_U32(p_ctx, flags, "dwFlags");
      WRITE_U32(p_ctx, chunk_offset, "dwOffset");
      WRITE_U32(p_ctx, chunk_size, "dwSize");

      chunk_offset += ((chunk_size + 1) & ~1) + 8;
   }

   AVI_END_CHUNK(p_ctx);

   /* Note that currently, we might write a partial index but still set AVIF_HASINDEX */
   /* if ( STREAM_STATUS(p_ctx) != VC_CONTAINER_SUCCESS ) module->index_offset = 0 */

   return STREAM_STATUS(p_ctx);
}