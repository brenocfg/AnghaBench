#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_21__ {int offs; int /*<<< orphan*/  time_pos; int /*<<< orphan*/  index; scalar_t__ flags; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {TYPE_5__ chunk; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_20__ {TYPE_2__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_SEEK_FLAGS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_18__ {TYPE_1__* priv; } ;
struct TYPE_17__ {TYPE_3__* module; } ;
typedef  TYPE_5__ AVI_TRACK_CHUNK_STATE_T ;

/* Variables and functions */
 int AVI_INDEX_DELTAFRAME ; 
 scalar_t__ AVI_INDEX_OF_CHUNKS ; 
 int INT64_C (int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  READ_FOURCC (TYPE_4__*,char*) ; 
 unsigned int READ_U16 (TYPE_4__*,char*) ; 
 int READ_U32 (TYPE_4__*,char*) ; 
 int READ_U64 (TYPE_4__*,char*) ; 
 scalar_t__ READ_U8 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  SEEK (TYPE_4__*,int) ; 
 int /*<<< orphan*/  SKIP_U32 (TYPE_4__*,char*) ; 
 scalar_t__ STREAM_STATUS (TYPE_4__*) ; 
 int UINT64_C (int /*<<< orphan*/ ) ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_NOT_FOUND ; 
 scalar_t__ VC_CONTAINER_PACKET_FLAG_KEYFRAME ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  avi_calculate_chunk_time (TYPE_3__*) ; 
 scalar_t__ avi_check_track (TYPE_4__*,unsigned int,unsigned int) ; 
 int avi_compare_seek_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avi_track_from_chunk_id (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_scan_standard_index_chunk(VC_CONTAINER_T *p_ctx, uint64_t index_offset,
   unsigned seek_track_num, int64_t *time, VC_CONTAINER_SEEK_FLAGS_T flags, uint64_t *pos)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_NOT_FOUND;
   VC_CONTAINER_TRACK_MODULE_T *track_module = NULL;
   VC_CONTAINER_FOURCC_T chunk_id;
   uint32_t chunk_size;
   uint16_t data_type, track_num;
   uint8_t index_type, index_sub_type;
   uint32_t entry, entry_count = 0;
   uint16_t entry_size;
   uint64_t base_offset = UINT64_C(0);
   uint64_t position = UINT64_C(0);
   uint64_t prev_keyframe_offs = INT64_C(0);
   AVI_TRACK_CHUNK_STATE_T prev_keyframe_chunk = { 0 };

   SEEK(p_ctx, index_offset);

   chunk_id = READ_FOURCC(p_ctx, "Chunk ID");
   chunk_size = READ_U32(p_ctx, "Chunk Size");

   entry_size = READ_U16(p_ctx, "wLongsPerEntry");
   index_sub_type = READ_U8(p_ctx, "bIndexSubType");
   index_type = READ_U8(p_ctx, "bIndexType");
   entry_count = READ_U32(p_ctx, "nEntriesInUse");
   chunk_id = READ_FOURCC(p_ctx, "dwChunkId");
   base_offset = READ_U64(p_ctx, "qwBaseOffset");
   SKIP_U32(p_ctx, "dwReserved");

   if ((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS)
      return status;

   avi_track_from_chunk_id(chunk_id, &data_type, &track_num);
   status = avi_check_track(p_ctx, data_type, track_num);
   if (status || chunk_size < 24 || track_num != seek_track_num)
      return VC_CONTAINER_ERROR_FORMAT_INVALID;

   if (entry_size != 2 || index_sub_type != 0 || index_type != AVI_INDEX_OF_CHUNKS)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   entry_count = MIN(entry_count, (chunk_size - 24) / (entry_size * 4));

   track_module = p_ctx->tracks[seek_track_num]->priv->module;

   for (entry = 0; entry < entry_count; ++entry)
   {
      uint32_t chunk_offset;
      int key_frame = 0;

      chunk_offset = READ_U32(p_ctx, "dwOffset");
      chunk_size = READ_U32(p_ctx, "dwSize");

      if ((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS)
         break;

      status = VC_CONTAINER_ERROR_NOT_FOUND;

      if (!(chunk_size & AVI_INDEX_DELTAFRAME))
         key_frame = 1;
      chunk_size &= ~AVI_INDEX_DELTAFRAME;

      position = base_offset + chunk_offset - 8;

      if (key_frame)
         track_module->chunk.flags = VC_CONTAINER_PACKET_FLAG_KEYFRAME;
      else
         track_module->chunk.flags = 0;

      if (time != NULL)
      {
         int res;
         status = VC_CONTAINER_ERROR_NOT_FOUND;
         res = avi_compare_seek_time(track_module->chunk.time_pos, *time, key_frame, flags);

         if (res == 0)
         {
            *pos = position;
            *time = track_module->chunk.time_pos;
            status = VC_CONTAINER_SUCCESS;
            break;
         }
         else if (res > 0)
         {
            if (prev_keyframe_offs)
            {
               *pos = prev_keyframe_offs;
               track_module->chunk = prev_keyframe_chunk;
               *time = track_module->chunk.time_pos;
               status = VC_CONTAINER_SUCCESS;
            }
            break;
         }

         if (key_frame)
         {
            prev_keyframe_offs = position;
            prev_keyframe_chunk = track_module->chunk;
         }
      }
      else
      {
         /* Not seeking to a time position, but scanning
            track chunk state up to a certain file position
            instead */
         if (position >= *pos)
         {
            status = VC_CONTAINER_SUCCESS;
            break;
         }
      }

      track_module->chunk.index++;
      track_module->chunk.offs += chunk_size;
      track_module->chunk.time_pos = avi_calculate_chunk_time(track_module);
   }

   return status;
}