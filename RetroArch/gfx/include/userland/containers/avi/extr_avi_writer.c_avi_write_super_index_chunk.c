#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_22__ {int index_size; int chunk_offs; int chunk_index; scalar_t__ sample_size; scalar_t__ index_offset; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_23__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {scalar_t__ refcount; } ;
struct TYPE_24__ {TYPE_4__ null_io; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_20__ {TYPE_2__* priv; } ;
struct TYPE_19__ {TYPE_5__* module; } ;
struct TYPE_18__ {TYPE_7__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_END_CHUNK (TYPE_6__*) ; 
 int /*<<< orphan*/  AVI_INDEX_OF_INDEXES ; 
 scalar_t__ AVI_SUPER_INDEX_ENTRY_SIZE ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_6__*) ; 
 int /*<<< orphan*/  VC_FOURCC (char,unsigned char,char,char) ; 
 int /*<<< orphan*/  WRITE_BYTES (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WRITE_FOURCC (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U16 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U64 (TYPE_6__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avi_chunk_id_from_track_num (TYPE_6__*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_write_super_index_chunk(VC_CONTAINER_T *p_ctx, unsigned int index_track_num,
   uint32_t index_size)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[index_track_num]->priv->module;
   VC_CONTAINER_FOURCC_T chunk_id;
   uint32_t num_indices = 1; /* FIXME: support for multiple RIFF chunks (AVIX) */
   unsigned int i;

   if(module->null_io.refcount)
   {
      /* Assume that we're not actually writing the data, just want know the index chunk size */
      WRITE_BYTES(p_ctx, NULL, 8 + 24 + num_indices * (int64_t)AVI_SUPER_INDEX_ENTRY_SIZE);
      return STREAM_STATUS(p_ctx);
   }

   if (track_module->index_offset)
      WRITE_FOURCC(p_ctx, VC_FOURCC('i','n','d','x'), "Chunk ID");
   else
      WRITE_FOURCC(p_ctx, VC_FOURCC('J','U','N','K'), "Chunk ID");

   WRITE_U32(p_ctx, index_size, "Chunk Size");

   avi_chunk_id_from_track_num(p_ctx, &chunk_id, index_track_num);
   WRITE_U16(p_ctx, 4, "wLongsPerEntry");
   WRITE_U8(p_ctx, 0, "bIndexSubType");
   WRITE_U8(p_ctx, AVI_INDEX_OF_INDEXES, "bIndexType");
   WRITE_U32(p_ctx, num_indices, "nEntriesInUse");
   WRITE_FOURCC(p_ctx, chunk_id, "dwChunkId");
   WRITE_U32(p_ctx, 0, "dwReserved0");
   WRITE_U32(p_ctx, 0, "dwReserved1");
   WRITE_U32(p_ctx, 0, "dwReserved2");

   for (i = 0; i < num_indices; ++i)
   {
      uint64_t index_offset = track_module->index_offset;
      uint32_t chunk_size = track_module->index_size;
      uint32_t length = track_module->sample_size ?
         track_module->chunk_offs : track_module->chunk_index;
      WRITE_U64(p_ctx, index_offset, "qwOffset");
      WRITE_U32(p_ctx, chunk_size, "dwSize");
      WRITE_U32(p_ctx, length, "dwDuration");
   }

   AVI_END_CHUNK(p_ctx);

   return STREAM_STATUS(p_ctx);
}