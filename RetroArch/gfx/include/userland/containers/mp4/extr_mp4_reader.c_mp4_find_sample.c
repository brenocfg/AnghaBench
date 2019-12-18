#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int int64_t ;
struct TYPE_13__ {int timescale; TYPE_3__* sample_table; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_14__ {TYPE_2__** tracks; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {unsigned int entries; int /*<<< orphan*/  offset; } ;
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {TYPE_4__* module; } ;
typedef  int /*<<< orphan*/  MP4_READER_STATE_T ;

/* Variables and functions */
 scalar_t__ MAX (int,int) ; 
 size_t MP4_SAMPLE_TABLE_STTS ; 
 scalar_t__ SEEK (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ STREAM_STATUS (TYPE_5__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 void* _READ_U32 (TYPE_5__*) ; 

__attribute__((used)) static uint32_t mp4_find_sample( VC_CONTAINER_T *p_ctx, uint32_t track,
   MP4_READER_STATE_T *state, int64_t seek_time, VC_CONTAINER_STATUS_T *p_status )
{
   VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[track]->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint32_t sample = 0, sample_duration_count;
   int64_t sample_duration, seek_time_up = seek_time + 1;
   unsigned int i;
   VC_CONTAINER_PARAM_UNUSED(state);

   seek_time = seek_time * track_module->timescale / 1000000;
   /* We also need to check against the time rounded up to account for
    * rounding errors in the timestamp (because of the timescale conversion) */
   seek_time_up = seek_time_up * track_module->timescale / 1000000;

   status = SEEK(p_ctx, track_module->sample_table[MP4_SAMPLE_TABLE_STTS].offset);
   if(status != VC_CONTAINER_SUCCESS) goto end;

   /* Find the sample which corresponds to the requested time */
   for(i = 0; i < track_module->sample_table[MP4_SAMPLE_TABLE_STTS].entries; i++)
   {
      sample_duration_count = _READ_U32(p_ctx);
      sample_duration = _READ_U32(p_ctx);
      status = STREAM_STATUS(p_ctx);
      if(status != VC_CONTAINER_SUCCESS) break;

      if(sample_duration_count * sample_duration <= seek_time)
      {
         seek_time -= sample_duration_count * sample_duration;
         seek_time_up -= sample_duration_count * sample_duration;
         sample += sample_duration_count;
         continue;
      }
      if(!sample_duration) break;

      seek_time /= sample_duration;
      seek_time_up /= sample_duration;
      sample += MAX(seek_time, seek_time_up);
      break;
   }

 end:
   if(p_status) *p_status = status;
   return sample;
}