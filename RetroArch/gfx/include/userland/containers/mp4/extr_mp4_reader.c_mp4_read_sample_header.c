#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_19__ {int timescale; size_t samples_batch_size; TYPE_4__* sample_table; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_20__ {TYPE_2__** tracks; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {scalar_t__ status; scalar_t__ sample_offset; scalar_t__ sample_size; scalar_t__ sample; int pts; int dts; int duration; int sample_composition_offset; scalar_t__ next_sync_sample; int keyframe; scalar_t__ samples_in_chunk; scalar_t__ sample_duration; int /*<<< orphan*/  sample_duration_count; TYPE_3__* sample_table; int /*<<< orphan*/  sample_composition_count; int /*<<< orphan*/  chunks; int /*<<< orphan*/  offset; } ;
struct TYPE_18__ {scalar_t__ entries; } ;
struct TYPE_17__ {scalar_t__ entry; } ;
struct TYPE_16__ {TYPE_1__* priv; } ;
struct TYPE_15__ {TYPE_5__* module; } ;
typedef  TYPE_7__ MP4_READER_STATE_T ;

/* Variables and functions */
 size_t MP4_SAMPLE_TABLE_CTTS ; 
 size_t MP4_SAMPLE_TABLE_STCO ; 
 size_t MP4_SAMPLE_TABLE_STSC ; 
 size_t MP4_SAMPLE_TABLE_STSS ; 
 size_t MP4_SAMPLE_TABLE_STSZ ; 
 size_t MP4_SAMPLE_TABLE_STTS ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  mp4_log_state (TYPE_6__*,TYPE_7__*) ; 
 void* mp4_read_sample_table (TYPE_6__*,TYPE_5__*,TYPE_7__*,size_t,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_read_sample_header( VC_CONTAINER_T *p_ctx, uint32_t track,
   MP4_READER_STATE_T *state )
{
   VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[track]->priv->module;

   if(state->status != VC_CONTAINER_SUCCESS) return state->status;

   if(state->sample_offset < state->sample_size)
      return state->status; /* We still have data left from the current sample */

   /* Switch to the next sample */
   state->offset += state->sample_size;
   state->sample_offset = 0;
   state->sample_size = 0;
   state->sample++;

   if(!state->samples_in_chunk)
   {
      /* We're switching to the next chunk */
      if(!state->chunks)
      {
         /* Seek to the next entry in the STSC */
         state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STSC, 1 );
         if(state->status != VC_CONTAINER_SUCCESS) goto error;
      }

      /* Get the offset of the new chunk */
      state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STCO, 1 );
      if(state->status != VC_CONTAINER_SUCCESS) goto error;

      state->chunks--;
   }
   state->samples_in_chunk--;

   /* Get the new sample size */
   state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STSZ, 1 );
   if(state->status != VC_CONTAINER_SUCCESS) goto error;

   /* Get the timestamp */
   if(track_module->timescale)
      state->pts = state->dts = state->duration * 1000000 / track_module->timescale;
   if(!state->sample_duration_count)
   {
      state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STTS, 1 );
      if(state->status != VC_CONTAINER_SUCCESS) goto error;
   }
   state->sample_duration_count--;

   /* Get the composition time */
   if(track_module->sample_table[MP4_SAMPLE_TABLE_CTTS].entries)
   {
      if(!state->sample_composition_count)
      {
         state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_CTTS, 1 );
         if(state->status != VC_CONTAINER_SUCCESS) goto error;
      }
      if(track_module->timescale)
         state->pts = (state->duration + state->sample_composition_offset) * 1000000 / track_module->timescale;
      state->sample_composition_count--;
   }
   state->duration += state->sample_duration;

   /* Get the keyframe flag */
   if(state->sample_table[MP4_SAMPLE_TABLE_STSS].entry <
         track_module->sample_table[MP4_SAMPLE_TABLE_STSS].entries &&
      !state->next_sync_sample)
   {
      mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STSS, 1 );
      state->status = VC_CONTAINER_SUCCESS; /* This isn't a critical error */
   }

   state->keyframe =
      track_module->sample_table[MP4_SAMPLE_TABLE_STSS].entries &&
      state->sample == state->next_sync_sample;
   if(state->keyframe)
      state->next_sync_sample = 0;

   /* Try to batch several samples together if requested. We'll always stop at the chunk boundary */
   if(track_module->samples_batch_size)
   {
      uint32_t size = state->sample_size;
      while(state->samples_in_chunk && size < track_module->samples_batch_size)
      {
         if(mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STSZ, 1 )) break;

         if(!state->sample_duration_count)
            if(mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STTS, 1 )) break;

         state->sample_duration_count--;
         state->duration += state->sample_duration;

         size += state->sample_size;
         state->samples_in_chunk--;
         state->sample++;
      }
      state->sample_size = size;
   }

#ifdef ENABLE_MP4_READER_LOG_STATE
   mp4_log_state(p_ctx, state);
#endif

 error:
   return state->status;
}