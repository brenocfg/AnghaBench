#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_26__ {int chunk_index; int /*<<< orphan*/  index_size; int /*<<< orphan*/  index_offset; } ;
typedef  TYPE_6__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_27__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_7__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_25__ {int /*<<< orphan*/  io; } ;
struct TYPE_24__ {scalar_t__ refcount; } ;
struct TYPE_28__ {int data_offset; TYPE_5__ temp_io; TYPE_4__ null_io; } ;
typedef  TYPE_8__ VC_CONTAINER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_23__ {TYPE_2__* priv; } ;
struct TYPE_22__ {TYPE_6__* module; } ;
struct TYPE_21__ {TYPE_8__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_END_CHUNK (TYPE_7__*) ; 
 int AVI_INDEX_DELTAFRAME ; 
 int /*<<< orphan*/  AVI_INDEX_OF_CHUNKS ; 
 scalar_t__ AVI_STD_INDEX_ENTRY_SIZE ; 
 int INT64_C (int) ; 
 int /*<<< orphan*/  STREAM_POSITION (TYPE_7__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_7__*) ; 
 scalar_t__ ULONG_MAX ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_BYTES (TYPE_7__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WRITE_FOURCC (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U16 (TYPE_7__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_7__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U64 (TYPE_7__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avi_chunk_id_from_track_num (TYPE_7__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  avi_index_chunk_id_from_track_num (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ avi_read_index_entry (TYPE_7__*,unsigned int*,int*) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_container_io_seek (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_write_standard_index_chunk( VC_CONTAINER_T *p_ctx, unsigned int index_track_num,
   uint32_t index_size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[index_track_num]->priv->module;
   VC_CONTAINER_STATUS_T status;
   VC_CONTAINER_FOURCC_T chunk_id;
   int64_t base_offset = module->data_offset + 12;
   uint32_t num_chunks = track_module->chunk_index;
   uint32_t chunk_offset = 4;

   vc_container_assert(32 + num_chunks * (int64_t)AVI_STD_INDEX_ENTRY_SIZE <= (int64_t)ULONG_MAX);

   if(module->null_io.refcount)
   {
      /* Assume that we're not actually writing the data, just want know the index chunk size */
      WRITE_BYTES(p_ctx, NULL, 8 + 24 + num_chunks * INT64_C(8));
      return STREAM_STATUS(p_ctx);
   }

   track_module->index_offset = STREAM_POSITION(p_ctx);
   track_module->index_size = index_size ? (index_size - 8) : 0;

   avi_index_chunk_id_from_track_num(&chunk_id, index_track_num);
   WRITE_FOURCC(p_ctx, chunk_id, "Chunk ID");
   WRITE_U32(p_ctx, index_size, "Chunk Size");

   avi_chunk_id_from_track_num(p_ctx, &chunk_id, index_track_num);
   WRITE_U16(p_ctx, 2, "wLongsPerEntry");
   WRITE_U8(p_ctx, 0, "bIndexSubType");
   WRITE_U8(p_ctx, AVI_INDEX_OF_CHUNKS, "bIndexType");
   WRITE_U32(p_ctx, num_chunks, "nEntriesInUse");
   WRITE_FOURCC(p_ctx, chunk_id, "dwChunkId");
   WRITE_U64(p_ctx, base_offset, "qwBaseOffset");
   WRITE_U32(p_ctx, 0, "dwReserved");

   /* Scan through all written entries, convert to appropriate index format */
   vc_container_io_seek(module->temp_io.io, INT64_C(0));

   while(STREAM_STATUS(p_ctx) == VC_CONTAINER_SUCCESS)
   {
      uint32_t chunk_size;
      unsigned int track_num;

      status = avi_read_index_entry(p_ctx, &track_num, &chunk_size);
      if (status != VC_CONTAINER_SUCCESS) break;

      if(track_num != index_track_num) continue;

      WRITE_U32(p_ctx, chunk_offset, "dwOffset");
      WRITE_U32(p_ctx, chunk_size, "dwSize");

      chunk_offset += ((chunk_size + 1) & ~(1 | AVI_INDEX_DELTAFRAME)) + 12;
   }

   AVI_END_CHUNK(p_ctx);

   return STREAM_STATUS(p_ctx);
}