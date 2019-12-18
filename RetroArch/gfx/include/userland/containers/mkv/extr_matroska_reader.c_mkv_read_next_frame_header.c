#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  unsigned int int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_29__ {unsigned int number; int timecode_scale; int frame_duration; TYPE_4__* encodings; scalar_t__ encodings_num; } ;
typedef  TYPE_7__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_30__ {unsigned int tracks_num; TYPE_6__* priv; TYPE_3__** tracks; } ;
typedef  TYPE_8__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_31__ {scalar_t__ timecode_scale; } ;
typedef  TYPE_9__ VC_CONTAINER_MODULE_T ;
struct TYPE_28__ {int /*<<< orphan*/  io; TYPE_9__* module; } ;
struct TYPE_27__ {scalar_t__ id; scalar_t__ data_start; scalar_t__ data_offset; scalar_t__ size; scalar_t__ offset; } ;
struct TYPE_26__ {unsigned int data_size; int /*<<< orphan*/  data; } ;
struct TYPE_25__ {TYPE_2__* format; TYPE_1__* priv; } ;
struct TYPE_24__ {scalar_t__ es_type; } ;
struct TYPE_23__ {TYPE_7__* module; } ;
struct TYPE_22__ {size_t level; unsigned int lacing_num_frames; scalar_t__ lacing_size; unsigned int* lacing_sizes; scalar_t__ lacing_current_size; unsigned int track; int pts; scalar_t__ cluster_timecode; unsigned int flags; int frame_duration; unsigned int header_size; unsigned int header_size_backup; TYPE_5__* levels; int /*<<< orphan*/  header_data; int /*<<< orphan*/  seen_ref_block; } ;
typedef  TYPE_10__ MKV_READER_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_FORMAT (TYPE_8__*,char*,int) ; 
 scalar_t__ MKV_ELEMENT_ID_BLOCK ; 
 scalar_t__ MKV_ELEMENT_ID_SIMPLE_BLOCK ; 
 unsigned int MKV_MAX_LACING_NUM ; 
 unsigned int MKV_READ_SINT (TYPE_8__*,char*) ; 
 scalar_t__ MKV_READ_U16 (TYPE_8__*,char*) ; 
 void* MKV_READ_U8 (TYPE_8__*,char*) ; 
 unsigned int MKV_READ_UINT (TYPE_8__*,char*) ; 
 scalar_t__ STREAM_POSITION (TYPE_8__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_8__*) ; 
 scalar_t__ VC_CONTAINER_ERROR_CORRUPTED ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int VC_CONTAINER_TIME_UNKNOWN ; 
 scalar_t__ mkv_find_next_block (TYPE_8__*,TYPE_10__*) ; 
 unsigned int vc_container_io_read_uint8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_next_frame_header(VC_CONTAINER_T *p_ctx,
      MKV_READER_STATE_T *state, uint32_t *pi_track, uint32_t *pi_length)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = 0;
   unsigned int i, track, flags, is_first_lace = 0;
   int64_t size, pts;

   if ((state->levels[state->level].id == MKV_ELEMENT_ID_BLOCK ||
        state->levels[state->level].id == MKV_ELEMENT_ID_SIMPLE_BLOCK) &&
       state->levels[state->level].data_start + state->levels[state->level].data_offset <
          state->levels[state->level].size)
      goto end;

   status = mkv_find_next_block(p_ctx, state);
   if (status != VC_CONTAINER_SUCCESS) return status;

   /* We have a block */
   size = state->levels[state->level].size;
   track = MKV_READ_UINT(p_ctx, "Track Number"); LOG_FORMAT(p_ctx, "Track Number: %u", track);
   pts = (int16_t)MKV_READ_U16(p_ctx, "Timecode");
   flags = MKV_READ_U8(p_ctx, "Flags");
   if(state->levels[state->level].id == MKV_ELEMENT_ID_BLOCK) flags &= 0x0F;

   //TODO improve sanity checking
   /* Sanity checking */
   if(size < 0) return VC_CONTAINER_ERROR_CORRUPTED;
   if(STREAM_STATUS(p_ctx)) return STREAM_STATUS(p_ctx);

   for (i = 0; i < p_ctx->tracks_num; i++)
      if (p_ctx->tracks[i]->priv->module->number == track)
      { track_module = p_ctx->tracks[i]->priv->module; break; }

   /* Finding out if we have a keyframe when dealing with an MKV_ELEMENT_ID_BLOCK is tricky */
   if(state->levels[state->level].id == MKV_ELEMENT_ID_BLOCK &&
      i < p_ctx->tracks_num && p_ctx->tracks[i]->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
   {
      /* The absence of a ReferenceBlock element tells us if we are a keyframe or not.
       * The problem we have is that this element can appear before as well as after the block element.
       * To avoid seeking to look for this element, we do some guess work. */
      if(!state->seen_ref_block && state->level &&
         state->levels[state->level].offset + state->levels[state->level].size >=
            state->levels[state->level-1].offset + state->levels[state->level-1].size)
         flags |= 0x80;
   }

   /* Take care of the lacing */
   state->lacing_num_frames = 0;
   if(i < p_ctx->tracks_num && (flags & 0x06))
   {
      unsigned int i, value = 0;
      int32_t fs = 0;

      state->lacing_num_frames = MKV_READ_U8(p_ctx, "Lacing Head");
      state->lacing_size = 0;
      switch((flags & 0x06)>>1)
      {
      case 1:  /* Xiph lacing */
         for(i = 0; i < state->lacing_num_frames; i++, fs = 0)
         {
            do {
               value = vc_container_io_read_uint8(p_ctx->priv->io);
               fs += value; size--;
            } while(value == 255);
            LOG_FORMAT(p_ctx, "Frame Size: %i", (int)fs);
            if(state->lacing_num_frames > MKV_MAX_LACING_NUM) continue;
            state->lacing_sizes[state->lacing_num_frames-(i+1)] = fs;
         }
         break;
      case 3:  /* EBML lacing */
         for(i = 0; i < state->lacing_num_frames; i++)
         {
            if(!i) fs = MKV_READ_UINT(p_ctx, "Frame Size");
            else fs += MKV_READ_SINT(p_ctx, "Frame Size");
            LOG_FORMAT(p_ctx, "Frame Size: %i", (int)fs);
            if(state->lacing_num_frames > MKV_MAX_LACING_NUM) continue;
            state->lacing_sizes[state->lacing_num_frames-(i+1)] = fs;
         }
         break;
      default: /* Fixed-size lacing */
         state->lacing_size = size / (state->lacing_num_frames+1);
         break;
      }

      /* There is a max number of laced frames we can support but after we can still give back
       * all the other frames in 1 packet */
      if(state->lacing_num_frames > MKV_MAX_LACING_NUM)
         state->lacing_num_frames = MKV_MAX_LACING_NUM;

      /* Sanity check the size of the frames */
      if(size < 0) return VC_CONTAINER_ERROR_CORRUPTED;
      if(STREAM_STATUS(p_ctx)) return STREAM_STATUS(p_ctx);
      state->lacing_current_size = state->lacing_size;
      if(!state->lacing_size)
      {
         int64_t frames_size = 0;
         for(i = state->lacing_num_frames; i > 0; i--)
         {
            if(frames_size + state->lacing_sizes[i-1] > size) /* return error ? */
               state->lacing_sizes[i-1] = size - frames_size;
            frames_size += state->lacing_sizes[i-1];
         }
      }
      state->lacing_current_size = 0;
      state->lacing_num_frames++; /* Will be decremented further down */
      is_first_lace = 1;
   }

   state->track = i;
   state->pts = (state->cluster_timecode + pts) * module->timecode_scale;
   if(track_module) state->pts *= track_module->timecode_scale;
   state->pts /= 1000;
   state->flags = flags;

   state->frame_duration = state->frame_duration * module->timecode_scale / 1000;
   if(state->lacing_num_frames) state->frame_duration /= state->lacing_num_frames;
   if(!state->frame_duration && track_module)
      state->frame_duration = track_module->frame_duration / 1000;

   state->levels[state->level].data_start = STREAM_POSITION(p_ctx) -
      state->levels[state->level].offset;
   state->levels[state->level].data_offset = 0;

   /* Deal with header stripping compression */
   state->header_size = 0;
   if(track_module && track_module->encodings_num)
   {
      state->header_size = track_module->encodings[0].data_size;
      state->header_data = track_module->encodings[0].data;
   }
   state->header_size_backup = state->header_size;

 end:
   *pi_length = state->levels[state->level].size - state->levels[state->level].data_start -
      state->levels[state->level].data_offset + state->header_size;
   *pi_track = state->track;

   /* Special case for lacing */
   if(state->lacing_num_frames &&
      state->levels[state->level].data_offset >= state->lacing_current_size)
   {
      /* We need to switch to the next lace */
      if(--state->lacing_num_frames)
      {
         unsigned int lace_size = state->lacing_size;
         if(!state->lacing_size) lace_size = state->lacing_sizes[state->lacing_num_frames-1];
         state->lacing_current_size = lace_size;
      }
      state->levels[state->level].data_start += state->levels[state->level].data_offset;
      state->levels[state->level].data_offset = 0;
      if(!is_first_lace && state->frame_duration)
         state->pts += state->frame_duration;
      else if(!is_first_lace)
         state->pts = VC_CONTAINER_TIME_UNKNOWN;

      /* Deal with header stripping compression */
      state->header_data -= (state->header_size_backup - state->header_size);
      state->header_size = state->header_size_backup;
   }
   if(state->lacing_num_frames)
      *pi_length = state->lacing_current_size - state->levels[state->level].data_offset + state->header_size;

   return status == VC_CONTAINER_SUCCESS ? STREAM_STATUS(p_ctx) : status;
}