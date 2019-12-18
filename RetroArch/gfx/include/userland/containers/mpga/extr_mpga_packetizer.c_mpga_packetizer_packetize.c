#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_PACKETIZER_T ;
struct TYPE_9__ {int state; unsigned int version; unsigned int layer; unsigned int stream_version; unsigned int stream_layer; int /*<<< orphan*/  frame_size_samples; scalar_t__ frame_size; scalar_t__ bytes_read; int /*<<< orphan*/  sample_rate; scalar_t__ offset; int /*<<< orphan*/  lost_sync; int /*<<< orphan*/  channels; int /*<<< orphan*/  frame_bitrate; } ;
typedef  TYPE_3__ VC_PACKETIZER_MODULE_T ;
typedef  int VC_PACKETIZER_FLAGS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_TIME_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_10__ {scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BYTESTREAM_T ;
struct TYPE_7__ {int /*<<< orphan*/  time; int /*<<< orphan*/  stream; TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int MPGA_HEADER_SIZE ; 
#define  STATE_DATA 133 
#define  STATE_HEADER 132 
#define  STATE_SYNC 131 
#define  STATE_SYNC_DONE 130 
#define  STATE_SYNC_LOST 129 
#define  STATE_SYNC_NEXT 128 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_INCOMPLETE_DATA ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_CONTAINER_TIME_UNKNOWN ; 
 int VC_PACKETIZER_FLAG_FLUSH ; 
 int VC_PACKETIZER_FLAG_INFO ; 
 int VC_PACKETIZER_FLAG_SKIP ; 
 int /*<<< orphan*/  bytestream_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bytestream_get_timestamps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream_peek (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  bytestream_peek_at (int /*<<< orphan*/ *,scalar_t__,int*,int) ; 
 scalar_t__ bytestream_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bytestream_skip_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpga_read_header (int*,scalar_t__*,int /*<<< orphan*/ *,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  vc_container_time_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_time_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_time_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_time_set_samplerate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mpga_packetizer_packetize( VC_PACKETIZER_T *p_ctx,
   VC_CONTAINER_PACKET_T *out, VC_PACKETIZER_FLAGS_T flags )
{
   VC_PACKETIZER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_BYTESTREAM_T *stream = &p_ctx->priv->stream;
   VC_CONTAINER_TIME_T *time = &p_ctx->priv->time;
   uint8_t header[MPGA_HEADER_SIZE];
   VC_CONTAINER_STATUS_T status;
   unsigned int version, layer;
   int64_t pts, dts;

   while(1) switch (module->state)
   {
   case STATE_SYNC_LOST:
      bytestream_skip_byte( stream );
      if( !module->lost_sync++ )
         LOG_DEBUG(0, "lost sync");
      module->state = STATE_SYNC;

   case STATE_SYNC:
      while( bytestream_peek( stream, header, 2 ) == VC_CONTAINER_SUCCESS )
      {
          /* 11 bits sync work (0xffe) */
          if( header[0] == 0xff && (header[1] & 0xe0) == 0xe0 )
          {
             module->state = STATE_HEADER;
             break;
          }
          bytestream_skip_byte( stream );
          module->lost_sync++;
      }
      if( module->state != STATE_HEADER )
         return VC_CONTAINER_ERROR_INCOMPLETE_DATA; /* We need more data */

   case STATE_HEADER:
      if( bytestream_peek( stream, header, MPGA_HEADER_SIZE ) != VC_CONTAINER_SUCCESS )
         return VC_CONTAINER_ERROR_INCOMPLETE_DATA;

      status = mpga_read_header( header,
         &module->frame_size, &module->frame_bitrate, &module->version,
         &module->layer, &module->sample_rate, &module->channels,
         &module->frame_size_samples, &module->offset );
      if (status != VC_CONTAINER_SUCCESS)
      {
         LOG_ERROR(0, "invalid header");
         module->state = STATE_SYNC_LOST;
         break;
      }

      /* Version and layer are not allowed to change mid-stream */
      if ((module->stream_version && module->stream_version != module->version) ||
          (module->stream_layer && module->stream_layer != module->layer))
      {
         LOG_ERROR(0, "invalid header");
         module->state = STATE_SYNC_LOST;
         break;
      }
      /* We currently do not support free format streams  */
      if (!module->frame_size)
      {
         LOG_ERROR(0, "free format not supported");
         module->state = STATE_SYNC_LOST;
         break;
      }
      module->state = STATE_SYNC_NEXT;
      /* fall through to the next state */

   case STATE_SYNC_NEXT:
      /* To avoid being caught by emulated start codes, we also look at where the next frame is supposed to be */
      if( bytestream_peek_at( stream, module->frame_size, header, MPGA_HEADER_SIZE ) != VC_CONTAINER_SUCCESS )
      {
         /* If we know there won't be anymore data then we can just assume
          * we've got the frame we're looking for */
         if (flags & VC_PACKETIZER_FLAG_FLUSH)
         {
            module->state = STATE_SYNC_DONE;
            break;
         }
         return VC_CONTAINER_ERROR_INCOMPLETE_DATA;
      }

      status = mpga_read_header( header, 0, 0, &version, &layer, 0, 0, 0, 0 );
      if (status != VC_CONTAINER_SUCCESS)
      {
         LOG_ERROR(0, "invalid next header");
         module->state = STATE_SYNC_LOST;
         break;
      }

      /* Version and layer are not allowed to change mid-stream */
      if (module->version != version || module->layer != layer)
      {
         LOG_ERROR(0, "invalid header");
         module->state = STATE_SYNC_LOST;
         break;
      }

      module->state = STATE_SYNC_DONE;
      /* fall through to the next state */

   case STATE_SYNC_DONE:
      if( module->lost_sync )
         LOG_DEBUG(0, "recovered sync after %i bytes", module->lost_sync);
      module->lost_sync = 0;

      bytestream_skip( stream, module->offset );
      module->stream_version = module->version;
      module->stream_layer = module->layer;

      vc_container_time_set_samplerate(time, module->sample_rate, 1);
      bytestream_get_timestamps(stream, &pts, &dts, true);

      vc_container_time_set(time, pts);

      module->bytes_read = 0;
      module->state = STATE_DATA;
      /* fall through to the next state */

   case STATE_DATA:
      if( bytestream_size( stream ) < module->frame_size)
         return VC_CONTAINER_ERROR_INCOMPLETE_DATA;

      out->size = module->frame_size - module->bytes_read;
      out->pts = out->dts = VC_CONTAINER_TIME_UNKNOWN;
      out->flags = VC_CONTAINER_PACKET_FLAG_FRAME_END;

      if(!module->bytes_read)
      {
         out->pts = out->dts = vc_container_time_get(time);
         out->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_START;
      }

      if(flags & VC_PACKETIZER_FLAG_INFO)
         return VC_CONTAINER_SUCCESS;

      if(flags & VC_PACKETIZER_FLAG_SKIP)
      {
         bytestream_skip( stream, out->size );
      }
      else
      {
         out->size = MIN(out->size, out->buffer_size);
         bytestream_get( stream, out->data, out->size );
      }
      module->bytes_read += out->size;

      if(module->bytes_read == module->frame_size)
      {
         vc_container_time_add(time, module->frame_size_samples);
         module->state = STATE_HEADER;
      }
      return VC_CONTAINER_SUCCESS;

   default:
      break;
   };

   return VC_CONTAINER_SUCCESS;
}