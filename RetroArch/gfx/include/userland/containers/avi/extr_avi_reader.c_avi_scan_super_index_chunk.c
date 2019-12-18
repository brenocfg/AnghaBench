#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_20__ {TYPE_3__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_SEEK_FLAGS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_19__ {TYPE_2__* priv; } ;
struct TYPE_18__ {TYPE_1__* module; } ;
struct TYPE_17__ {scalar_t__ index_offset; int index_size; } ;

/* Variables and functions */
 scalar_t__ AVI_INDEX_OF_CHUNKS ; 
 scalar_t__ AVI_INDEX_OF_INDEXES ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  READ_FOURCC (TYPE_4__*,char*) ; 
 unsigned int READ_U16 (TYPE_4__*,char*) ; 
 int READ_U32 (TYPE_4__*,char*) ; 
 scalar_t__ READ_U64 (TYPE_4__*,char*) ; 
 scalar_t__ READ_U8 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  SEEK (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  SKIP_U32 (TYPE_4__*,char*) ; 
 scalar_t__ STREAM_POSITION (TYPE_4__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_4__*) ; 
 scalar_t__ UINT64_C (int /*<<< orphan*/ ) ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_NOT_FOUND ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ avi_check_track (TYPE_4__*,unsigned int,unsigned int) ; 
 scalar_t__ avi_scan_standard_index_chunk (TYPE_4__*,scalar_t__,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  avi_track_from_chunk_id (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_scan_super_index_chunk(VC_CONTAINER_T *p_ctx, unsigned index_track_num,
   int64_t *time, VC_CONTAINER_SEEK_FLAGS_T flags, uint64_t *pos)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_NOT_FOUND;
   VC_CONTAINER_FOURCC_T chunk_id;
   uint64_t index_offset;
   uint32_t index_size;
   uint16_t data_type, track_num;
   uint32_t entry, entry_count;
   uint16_t entry_size;
   uint8_t index_sub_type, index_type;

   index_offset = p_ctx->tracks[index_track_num]->priv->module->index_offset;
   index_size = p_ctx->tracks[index_track_num]->priv->module->index_size;

   SEEK(p_ctx, index_offset);

   entry_size = READ_U16(p_ctx, "wLongsPerEntry");
   index_sub_type = READ_U8(p_ctx, "bIndexSubType");
   index_type = READ_U8(p_ctx, "bIndexType");
   entry_count = READ_U32(p_ctx, "nEntriesInUse");
   chunk_id = READ_FOURCC(p_ctx, "dwChunkId");
   SKIP_U32(p_ctx, "dwReserved0");
   SKIP_U32(p_ctx, "dwReserved1");
   SKIP_U32(p_ctx, "dwReserved2");

   if ((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS)
      return status;

   if (index_type == AVI_INDEX_OF_INDEXES)
   {
      avi_track_from_chunk_id(chunk_id, &data_type, &track_num);
      status = avi_check_track(p_ctx, data_type, track_num);
      if (status || index_size < 24 || track_num != index_track_num) return VC_CONTAINER_ERROR_FORMAT_INVALID;

      /* FIXME: We should probably support AVI_INDEX_2FIELD as well */
      if (entry_size != 4 || index_sub_type != 0)
         return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

      entry_count = MIN(entry_count, (index_size - 24) / entry_size);

      for (entry = 0; entry < entry_count; ++entry)
      {
         uint64_t entry_offset, standard_index_offset;
         standard_index_offset = READ_U64(p_ctx, "qwOffset");
         SKIP_U32(p_ctx, "dwSize");
         SKIP_U32(p_ctx, "dwDuration");

         if ((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS)
            break;

         if (standard_index_offset == UINT64_C(0))
         {
            status = VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED; /* Not plausible */
            break;
         }

         entry_offset = STREAM_POSITION(p_ctx);
         status = avi_scan_standard_index_chunk(p_ctx, standard_index_offset, index_track_num, time, flags, pos);
         if (status != VC_CONTAINER_ERROR_NOT_FOUND) break;
         SEEK(p_ctx, entry_offset); /* Move to next entry ('ix' chunk); */
      }
   }
   else if (index_type == AVI_INDEX_OF_CHUNKS)
   {
      /* It seems we are dealing with a standard index instead... */
      status = avi_scan_standard_index_chunk(p_ctx, index_offset, index_track_num, time, flags, pos);
   }
   else
   {
      status = VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   }

   return status;
}