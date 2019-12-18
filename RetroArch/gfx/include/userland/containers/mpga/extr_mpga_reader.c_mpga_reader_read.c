#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  is_enabled; } ;
typedef  TYPE_2__ VC_CONTAINER_TRACK_T ;
struct TYPE_15__ {void* duration; TYPE_2__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_16__ {scalar_t__ size; scalar_t__ pts; int /*<<< orphan*/  data; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  dts; int /*<<< orphan*/  flags; int /*<<< orphan*/  track; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
struct TYPE_17__ {scalar_t__ frame_data_left; int bitrate; int frame_bitrate; scalar_t__ frame_size; scalar_t__ frame_time_pos; scalar_t__ frame_index; scalar_t__ frame_offset; void* data_size; void* num_frames; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_13__ {TYPE_5__* module; } ;

/* Variables and functions */
 void* MAX (void*,scalar_t__) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ READ_BYTES (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SKIP_BYTES (TYPE_3__*,scalar_t__) ; 
 scalar_t__ STREAM_STATUS (TYPE_3__*) ; 
 scalar_t__ VC_CONTAINER_ERROR_CONTINUE ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_CONTAINER_TIME_UNKNOWN ; 
 scalar_t__ mpga_calculate_frame_time (TYPE_3__*) ; 
 scalar_t__ mpga_sync (TYPE_3__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mpga_reader_read( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *p_packet, uint32_t flags )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[0];
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   if (module->frame_data_left == 0)
   {
      status = mpga_sync(p_ctx);
      if (status != VC_CONTAINER_SUCCESS) goto error;
   }

   if (module->bitrate)
   {
      /* Simple moving average over bitrate values seen so far */
      module->bitrate = (module->bitrate * 31 + module->frame_bitrate) >> 5;
   }
   else
   {
      module->bitrate = module->frame_bitrate;
   }

   /* Check if we can skip the frame straight-away */
   if (!track->is_enabled ||
       ((flags & VC_CONTAINER_READ_FLAG_SKIP) && !(flags & VC_CONTAINER_READ_FLAG_INFO)))
   {
      /* Just skip the frame */
      SKIP_BYTES(p_ctx, module->frame_size);
      module->frame_data_left = 0;
      if(!track->is_enabled)
         status = VC_CONTAINER_ERROR_CONTINUE;
      goto end;
   }

   /* Fill in packet information */
   p_packet->flags = p_packet->track = 0;
   if (module->frame_data_left == module->frame_size)
      p_packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME;
   else
      p_packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_END;

   p_packet->size = module->frame_data_left;

   p_packet->pts = module->frame_time_pos;
   p_packet->dts = VC_CONTAINER_TIME_UNKNOWN;

   if ((flags & VC_CONTAINER_READ_FLAG_SKIP))
   {
      SKIP_BYTES(p_ctx, module->frame_size);
      module->frame_data_left = 0;
      goto end;
   }

   if (flags & VC_CONTAINER_READ_FLAG_INFO)
      return VC_CONTAINER_SUCCESS;

   p_packet->size = MIN(p_packet->buffer_size, module->frame_data_left);
   p_packet->size = READ_BYTES(p_ctx, p_packet->data, p_packet->size);
   module->frame_data_left -= p_packet->size;

 end:
   if (module->frame_data_left == 0)
   {
      module->frame_index++;
      module->frame_offset += module->frame_size;
      module->frame_time_pos = mpga_calculate_frame_time(p_ctx);

#if 0 /* FIXME: is this useful e.g. progressive download? */
      module->num_frames = MAX(module->num_frames, module->frame_index);
      module->data_size = MAX(module->data_size, module->frame_offset);
      p_ctx->duration = MAX(p_ctx->duration, mpga_calculate_frame_time(p_ctx));
#endif
   }

   return status == VC_CONTAINER_SUCCESS ? STREAM_STATUS(p_ctx) : status;

error:
   return status;
}