#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_27__ {TYPE_6__* sample_table; } ;
typedef  TYPE_7__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_28__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_8__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_29__ {size_t track; scalar_t__ size; } ;
typedef  TYPE_9__ VC_CONTAINER_PACKET_T ;
struct TYPE_25__ {int /*<<< orphan*/  io; } ;
struct TYPE_24__ {scalar_t__ refcount; } ;
struct TYPE_20__ {size_t current_track; TYPE_5__ temp; TYPE_4__ null; } ;
typedef  TYPE_10__ VC_CONTAINER_MODULE_T ;
struct TYPE_26__ {int entries; } ;
struct TYPE_23__ {TYPE_2__* priv; } ;
struct TYPE_22__ {TYPE_7__* module; } ;
struct TYPE_21__ {TYPE_10__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_C (int /*<<< orphan*/ ) ; 
 size_t MP4_SAMPLE_TABLE_STSC ; 
 scalar_t__ STREAM_STATUS (TYPE_8__*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_BYTES (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_U24 (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_8__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mp4_writer_read_sample_from_temp (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_container_io_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_stsc( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[module->current_track]->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_PACKET_T sample;
   int64_t offset = 0, track_offset = -1;
   unsigned int entries = 0, chunks = 0, first_chunk = 0, samples_in_chunk = 0;

   memset(&sample, 0, sizeof(VC_CONTAINER_PACKET_T));

   WRITE_U8(p_ctx,  0, "version");
   WRITE_U24(p_ctx, 0, "flags");
   WRITE_U32(p_ctx, track_module->sample_table[MP4_SAMPLE_TABLE_STSC].entries, "entry_count");

   if(module->null.refcount)
   {
      /* We're not actually writing the data, we just want the size */
      WRITE_BYTES(p_ctx, 0, track_module->sample_table[MP4_SAMPLE_TABLE_STSC].entries * 12);
      return STREAM_STATUS(p_ctx);
   }

   /* Go through all the samples written */
   vc_container_io_seek(module->temp.io, INT64_C(0));

   status = mp4_writer_read_sample_from_temp(p_ctx, &sample);
   while(status == VC_CONTAINER_SUCCESS)
   {
      if(sample.track != module->current_track) goto skip;

      /* Is it a new chunk ? */
      if(track_offset != offset)
      {
         chunks++;
         if(samples_in_chunk)
         {
            WRITE_U32(p_ctx,  first_chunk, "first_chunk");
            WRITE_U32(p_ctx,  samples_in_chunk, "samples_per_chunk");
            WRITE_U32(p_ctx,  1, "sample_description_index");
            entries++;
         }
         first_chunk = chunks;
         samples_in_chunk = 0;
      }
      track_offset = offset + sample.size;
      samples_in_chunk++;

     skip:
      offset += sample.size;
      status = mp4_writer_read_sample_from_temp(p_ctx, &sample);
   }

   if(samples_in_chunk)
   {
      WRITE_U32(p_ctx,  first_chunk, "first_chunk");
      WRITE_U32(p_ctx,  samples_in_chunk, "samples_per_chunk");
      WRITE_U32(p_ctx,  1, "sample_description_index");
      entries++;
   }

   vc_container_assert(entries == track_module->sample_table[MP4_SAMPLE_TABLE_STSC].entries);

   return STREAM_STATUS(p_ctx);
}