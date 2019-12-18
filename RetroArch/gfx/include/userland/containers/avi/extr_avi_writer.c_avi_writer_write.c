#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_33__ {TYPE_3__* format; TYPE_5__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_TRACK_T ;
struct TYPE_34__ {scalar_t__ chunk_offs; void* max_chunk_size; int /*<<< orphan*/  chunk_index; } ;
typedef  TYPE_7__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_35__ {TYPE_6__** tracks; TYPE_4__* priv; } ;
typedef  TYPE_8__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_36__ {size_t track; int flags; scalar_t__ frame_size; scalar_t__ size; int data; } ;
typedef  TYPE_9__ VC_CONTAINER_PACKET_T ;
struct TYPE_27__ {int headers_written; scalar_t__ data_offset; scalar_t__ chunk_data_written; size_t current_track_num; scalar_t__ chunk_size; int avi_frame_buffer; TYPE_9__ frame_packet; } ;
typedef  TYPE_10__ VC_CONTAINER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_32__ {TYPE_7__* module; } ;
struct TYPE_31__ {TYPE_10__* module; } ;
struct TYPE_30__ {scalar_t__ es_type; TYPE_2__* type; } ;
struct TYPE_28__ {scalar_t__ block_align; } ;
struct TYPE_29__ {TYPE_1__ audio; } ;

/* Variables and functions */
 scalar_t__ AVI_AUDIO_CHUNK_SIZE_LIMIT ; 
 scalar_t__ AVI_FRAME_BUFFER_SIZE ; 
 int /*<<< orphan*/  AVI_PACKET_IS_KEYFRAME (int) ; 
 scalar_t__ INT64_C (int /*<<< orphan*/ ) ; 
 void* MAX (void*,scalar_t__) ; 
 scalar_t__ STREAM_POSITION (TYPE_8__*) ; 
 scalar_t__ STREAM_SEEKABLE (TYPE_8__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_8__*) ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_IO_FLUSH ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_RESOURCES ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 int VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  WRITE_BYTES (TYPE_8__*,int,scalar_t__) ; 
 int /*<<< orphan*/  WRITE_FOURCC (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_8__*,scalar_t__,char*) ; 
 scalar_t__ avi_calculate_file_size (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  avi_chunk_id_from_track_num (TYPE_8__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ avi_finish_data_chunk (TYPE_8__*,scalar_t__) ; 
 scalar_t__ avi_num_chunks (TYPE_8__*) ; 
 scalar_t__ avi_write_headers (TYPE_8__*) ; 
 int /*<<< orphan*/  avi_write_index_entry (TYPE_8__*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int,int,scalar_t__) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_container_control (TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_writer_write( VC_CONTAINER_T *p_ctx,
                                               VC_CONTAINER_PACKET_T *p_packet )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_TRACK_T *track = NULL;
   VC_CONTAINER_TRACK_MODULE_T *track_module = NULL;

   /* Check we have written headers before any data */
   if(!module->headers_written)
   {
      if ((status = avi_write_headers(p_ctx)) != VC_CONTAINER_SUCCESS) return status;
      module->headers_written = 1;
   }

   /* Check that we have started the 'movi' list */
   if (!module->data_offset)
   {
      module->data_offset = STREAM_POSITION(p_ctx);
      vc_container_assert(module->data_offset != INT64_C(0));

      WRITE_FOURCC(p_ctx, VC_FOURCC('L','I','S','T'), "Chunk ID");
      WRITE_U32(p_ctx, 0, "LIST Size");
      WRITE_FOURCC(p_ctx, VC_FOURCC('m','o','v','i'), "Chunk ID");
      if ((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS) return status;
   }

   /* If the container is passing in a frame from a new track but we
      arent't finished with a chunk from another track we need to finish
      that chunk first */
   if (module->chunk_data_written && p_packet->track != module->current_track_num)
   {
      track_module = p_ctx->tracks[module->current_track_num]->priv->module;
      status = avi_finish_data_chunk(p_ctx, module->chunk_data_written);
      avi_write_index_entry(p_ctx, module->current_track_num, module->chunk_data_written, 0);
      track_module->chunk_index++;
      track_module->chunk_offs += module->chunk_data_written;
      track_module->max_chunk_size = MAX(track_module->max_chunk_size, module->chunk_data_written);
      module->chunk_data_written = 0;
      if (status != VC_CONTAINER_SUCCESS) return status;
   }

   /* Check we are not about to go over the limit of total number of chunks */
   if (avi_num_chunks(p_ctx) == (uint32_t)ULONG_MAX) return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;

    if(STREAM_SEEKABLE(p_ctx))
    {
       /* Check we are not about to go over the maximum file size */
       if (avi_calculate_file_size(p_ctx, p_packet) >= (int64_t)ULONG_MAX) return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;
    }

   /* FIXME: are we expected to handle this case or should it be picked up by the above layer? */
   vc_container_assert(!(module->chunk_data_written && (p_packet->flags & VC_CONTAINER_PACKET_FLAG_FRAME_START)));

   track = p_ctx->tracks[p_packet->track];
   track_module = p_ctx->tracks[p_packet->track]->priv->module;
   module->current_track_num = p_packet->track;

   if (module->chunk_data_written == 0)
   {
      /* This is the first fragment of the chunk */
      VC_CONTAINER_FOURCC_T chunk_id;
      uint32_t chunk_size;

      avi_chunk_id_from_track_num(p_ctx, &chunk_id, p_packet->track);

      if (p_packet->frame_size)
      {
         /* We know what the final size of the chunk is going to be */
         chunk_size = module->chunk_size = p_packet->frame_size;
      }
      else
      {
         chunk_size = p_packet->size;
         module->chunk_size = 0;
      }

      WRITE_FOURCC(p_ctx, chunk_id, "Chunk ID");
      if(STREAM_SEEKABLE(p_ctx) || p_packet->flags & VC_CONTAINER_PACKET_FLAG_FRAME_END)
      {
         /* If the output stream can seek we can fix up the frame size later, and if the
          * packet holds the whole frame we won't need to, so write data straight out. */
         WRITE_U32(p_ctx, chunk_size, "Chunk Size");
         WRITE_BYTES(p_ctx, p_packet->data, p_packet->size);
      }
      else
      {
         vc_container_assert(module->avi_frame_buffer);
         if(p_packet->size > AVI_FRAME_BUFFER_SIZE)
            return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;
         module->frame_packet = *p_packet;
         module->frame_packet.data = module->avi_frame_buffer;
         memcpy(module->frame_packet.data,
                  p_packet->data, module->frame_packet.size);
      }

      module->chunk_data_written = p_packet->size;
   }
   else
   {
      if(module->frame_packet.size > 0 && module->avi_frame_buffer)
      {
         if(module->frame_packet.size > 0)
         {
            if(module->frame_packet.size + p_packet->size > AVI_FRAME_BUFFER_SIZE)
               return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;
            memcpy(module->frame_packet.data + module->frame_packet.size,
                     p_packet->data, p_packet->size);
            module->frame_packet.size += p_packet->size;
         }
      }
      else
      {
         WRITE_BYTES(p_ctx, p_packet->data, p_packet->size);
      }
      module->chunk_data_written += p_packet->size;
   }

   if ((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS)
      return status;

   if ((p_packet->flags & VC_CONTAINER_PACKET_FLAG_FRAME_END) ||
       (track->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO &&
        track->format->type->audio.block_align &&
        module->chunk_data_written > AVI_AUDIO_CHUNK_SIZE_LIMIT))
   {
      if(module->frame_packet.size > 0)
      {
         WRITE_U32(p_ctx, module->frame_packet.size, "Chunk Size");
         WRITE_BYTES(p_ctx, module->frame_packet.data, module->frame_packet.size);
         p_packet->size = module->frame_packet.size;
         module->frame_packet.size = 0;
      }

      if (!module->chunk_size && module->chunk_data_written > p_packet->size)
      {
         /* The chunk size needs to be rewritten */
         status = avi_finish_data_chunk(p_ctx, module->chunk_data_written);
      }
      else
      {
         status = avi_finish_data_chunk(p_ctx, 0);
      }

      if(!STREAM_SEEKABLE(p_ctx))
      {
         /* If we are streaming then flush to avoid delaying data transport. */
         vc_container_control(p_ctx, VC_CONTAINER_CONTROL_IO_FLUSH);
      }

      if(STREAM_SEEKABLE(p_ctx))
      {
          /* Keep track of data written so we can check we don't exceed file size and also for doing
           * index fix-ups, but only do this if we are writing to a seekable IO. */
          avi_write_index_entry(p_ctx, p_packet->track, module->chunk_data_written, AVI_PACKET_IS_KEYFRAME(p_packet->flags));
      }
      track_module->chunk_index++;
      track_module->chunk_offs += module->chunk_data_written;
      track_module->max_chunk_size = MAX(track_module->max_chunk_size, module->chunk_data_written);
      module->chunk_data_written = 0;

      if (status != VC_CONTAINER_SUCCESS) return status;
   }

   return STREAM_STATUS(p_ctx);
}