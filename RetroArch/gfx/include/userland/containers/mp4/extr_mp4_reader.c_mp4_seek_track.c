#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_20__ {TYPE_4__* sample_table; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_21__ {TYPE_2__** tracks; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  void* VC_CONTAINER_STATUS_T ;
struct TYPE_22__ {size_t chunks; size_t samples_per_chunk; size_t sample_duration_count; int duration; int sample_duration; size_t sample_composition_count; size_t next_sync_sample; size_t sample; void* status; scalar_t__ sample_size; int /*<<< orphan*/  samples_in_chunk; int /*<<< orphan*/  offset; TYPE_3__* sample_table; } ;
struct TYPE_19__ {unsigned int entries; } ;
struct TYPE_18__ {size_t entry; } ;
struct TYPE_17__ {TYPE_1__* priv; } ;
struct TYPE_16__ {TYPE_5__* module; } ;
typedef  TYPE_7__ MP4_READER_STATE_T ;

/* Variables and functions */
 size_t MP4_SAMPLE_TABLE_CO64 ; 
 size_t MP4_SAMPLE_TABLE_CTTS ; 
 size_t MP4_SAMPLE_TABLE_STCO ; 
 size_t MP4_SAMPLE_TABLE_STSC ; 
 size_t MP4_SAMPLE_TABLE_STSS ; 
 size_t MP4_SAMPLE_TABLE_STSZ ; 
 size_t MP4_SAMPLE_TABLE_STTS ; 
 void* VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp4_read_sample_header (TYPE_6__*,size_t,TYPE_7__*) ; 
 void* mp4_read_sample_table (TYPE_6__*,TYPE_5__*,TYPE_7__*,size_t,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_seek_track( VC_CONTAINER_T *p_ctx, uint32_t track,
   MP4_READER_STATE_T *state, uint32_t sample )
{
   VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[track]->priv->module;
   uint32_t chunk = 0, samples;
   unsigned int i;

   memset(state, 0, sizeof(*state));

   /* Find the right chunk */
   for(i = 0, samples = sample; i < track_module->sample_table[MP4_SAMPLE_TABLE_STSC].entries; i++)
   {
      state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STSC, 1 );
      if(state->status != VC_CONTAINER_SUCCESS) goto error;

      if(state->chunks * state->samples_per_chunk <= samples)
      {
         samples -= state->chunks * state->samples_per_chunk;
         chunk += state->chunks;
         continue;
      }

      while(samples >= state->samples_per_chunk)
      {
         samples -= state->samples_per_chunk;
         state->chunks--;
         chunk++;
      }

      state->chunks--;
      break;
   }

   /* Get the offset of the selected chunk */
   state->sample_table[MP4_SAMPLE_TABLE_STCO].entry = chunk;
   state->sample_table[MP4_SAMPLE_TABLE_CO64].entry = chunk;
   state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STCO, 1 );
   if(state->status != VC_CONTAINER_SUCCESS) goto error;

   /* Find the sample offset within the chunk */
   state->sample_table[MP4_SAMPLE_TABLE_STSZ].entry = sample - samples;
   for(i = 0; i < samples; i++)
   {
      state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STSZ, !i );
      if(state->status != VC_CONTAINER_SUCCESS) goto error;
      state->offset += state->sample_size;
      state->samples_in_chunk--;
   }

   /* Get the timestamp */
   for(i = 0, samples = sample; i < track_module->sample_table[MP4_SAMPLE_TABLE_STTS].entries; i++)
   {
      state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STTS, !i );
      if(state->status != VC_CONTAINER_SUCCESS) goto error;

      if(state->sample_duration_count <= samples)
      {
         samples -= state->sample_duration_count;
         state->duration += state->sample_duration * state->sample_duration_count;
         continue;
      }

      state->sample_duration_count -= samples;
      state->duration += samples * state->sample_duration;
      break;
   }

   /* Find the right place in the sample composition table */
   for(i = 0, samples = sample; i < track_module->sample_table[MP4_SAMPLE_TABLE_CTTS].entries; i++)
   {
      state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_CTTS, !i );
      if(state->status != VC_CONTAINER_SUCCESS) goto error;

      if(state->sample_composition_count <= samples)
      {
         samples -= state->sample_composition_count;
         continue;
      }

      state->sample_composition_count -= samples;
      break;
   }

   /* Find the right place in the synchronisation table */
   for(i = 0; i < track_module->sample_table[MP4_SAMPLE_TABLE_STSS].entries; i++)
   {
      state->status = mp4_read_sample_table( p_ctx, track_module, state, MP4_SAMPLE_TABLE_STSS, !i );
      if(state->status != VC_CONTAINER_SUCCESS) goto error;

      if(state->next_sync_sample >= sample + 1) break;
   }

   state->sample = sample;
   state->sample_size = 0;
   mp4_read_sample_header(p_ctx, track, state);

 error:
   return state->status;
}