#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_PACKETIZER_T ;
struct TYPE_10__ {int state; size_t max_frame_size; size_t frame_size; size_t bytes_per_sample; size_t bytes_read; size_t conversion_factor; size_t samples_per_frame; int /*<<< orphan*/  conversion; } ;
typedef  TYPE_3__ VC_PACKETIZER_MODULE_T ;
typedef  int VC_PACKETIZER_FLAGS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_TIME_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {size_t size; int /*<<< orphan*/  data; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BYTESTREAM_T ;
struct TYPE_8__ {int /*<<< orphan*/  time; int /*<<< orphan*/  stream; TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERSION_NONE ; 
 size_t FACTOR_SHIFT ; 
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
#define  STATE_DATA 129 
#define  STATE_NEW_PACKET 128 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_INCOMPLETE_DATA ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_CONTAINER_TIME_UNKNOWN ; 
 int VC_PACKETIZER_FLAG_FLUSH ; 
 int VC_PACKETIZER_FLAG_INFO ; 
 int VC_PACKETIZER_FLAG_SKIP ; 
 int /*<<< orphan*/  bytestream_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bytestream_get_timestamps_and_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int) ; 
 size_t bytestream_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream_skip (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  convert_pcm (TYPE_2__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_time_add (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vc_container_time_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_time_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T pcm_packetizer_packetize( VC_PACKETIZER_T *p_ctx,
   VC_CONTAINER_PACKET_T *out, VC_PACKETIZER_FLAGS_T flags )
{
   VC_PACKETIZER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_BYTESTREAM_T *stream = &p_ctx->priv->stream;
   VC_CONTAINER_TIME_T *time = &p_ctx->priv->time;
   int64_t pts, dts;
   size_t offset, size;

   while(1) switch (module->state)
   {
   case STATE_NEW_PACKET:
      /* Make sure we've got enough data */
      if(bytestream_size(stream) < module->max_frame_size &&
         !(flags & VC_PACKETIZER_FLAG_FLUSH))
         return VC_CONTAINER_ERROR_INCOMPLETE_DATA;
      if(!bytestream_size(stream))
         return VC_CONTAINER_ERROR_INCOMPLETE_DATA;

      module->frame_size = bytestream_size(stream);
      if(module->frame_size > module->max_frame_size)
         module->frame_size = module->max_frame_size;
      bytestream_get_timestamps_and_offset(stream, &pts, &dts, &offset, true);
      vc_container_time_set(time, pts);
      if(pts != VC_CONTAINER_TIME_UNKNOWN)
         vc_container_time_add(time, offset / module->bytes_per_sample);

      module->bytes_read = 0;
      module->state = STATE_DATA;
      /* fall through to the next state */

   case STATE_DATA:
      size = module->frame_size - module->bytes_read;
      out->pts = out->dts = VC_CONTAINER_TIME_UNKNOWN;
      out->flags = VC_CONTAINER_PACKET_FLAG_FRAME_END;
      out->size = (size * module->conversion_factor) >> FACTOR_SHIFT;

      if(!module->bytes_read)
      {
         out->pts = out->dts = vc_container_time_get(time);
         out->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_START;
      }

      if(flags & VC_PACKETIZER_FLAG_INFO)
         return VC_CONTAINER_SUCCESS;

      if(flags & VC_PACKETIZER_FLAG_SKIP)
      {
         bytestream_skip( stream, size );
      }
      else
      {
         out->size = MIN(out->size, out->buffer_size);
         size = (out->size << FACTOR_SHIFT) / module->conversion_factor;
         out->size = (size * module->conversion_factor) >> FACTOR_SHIFT;

         if(module->conversion != CONVERSION_NONE)
            convert_pcm(p_ctx, stream, size, out->data);
         else
            bytestream_get(stream, out->data, out->size);
      }
      module->bytes_read += size;

      if(module->bytes_read == module->frame_size)
      {
         vc_container_time_add(time, module->samples_per_frame);
         module->state = STATE_NEW_PACKET;
      }
      return VC_CONTAINER_SUCCESS;

   default:
      break;
   };

   return VC_CONTAINER_SUCCESS;
}