#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  float int16_t ;
struct TYPE_21__ {unsigned int length; int flags; scalar_t__ offset; scalar_t__ data; } ;
struct TYPE_20__ {int /*<<< orphan*/  queue; } ;
struct TYPE_19__ {TYPE_1__* priv; } ;
struct TYPE_18__ {TYPE_4__* format; TYPE_6__* component; } ;
struct TYPE_17__ {scalar_t__ encoding; TYPE_3__* es; } ;
struct TYPE_15__ {int bits_per_sample; } ;
struct TYPE_16__ {TYPE_2__ audio; } ;
struct TYPE_14__ {TYPE_7__* module; } ;
typedef  TYPE_5__ MMAL_PORT_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;
typedef  TYPE_7__ MMAL_COMPONENT_MODULE_T ;
typedef  TYPE_8__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int MMAL_BUFFER_HEADER_FLAG_EOS ; 
 scalar_t__ MMAL_ENCODING_PCM_FLOAT ; 
 scalar_t__ MMAL_ENCODING_PCM_SIGNED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  mmal_event_eos_send (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_5__*,TYPE_8__*) ; 
 TYPE_8__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put_back (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static void sdl_callback( void *ctx, uint8_t *stream, int size )
{
   MMAL_PORT_T *port = (MMAL_PORT_T *)ctx;
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   MMAL_BUFFER_HEADER_T *buffer;
   unsigned int i, bytes;

   while (size > 0)
   {
      buffer = mmal_queue_get(module->queue);
      if (!buffer)
      {
         LOG_ERROR("audio underrun");
         return;
      }

      if (port->format->encoding == MMAL_ENCODING_PCM_SIGNED &&
          port->format->es->audio.bits_per_sample == 16)
      {
         bytes = buffer->length;
         if (bytes > (unsigned int)size) bytes = size;
         memcpy(stream, buffer->data + buffer->offset, bytes);
         buffer->offset += bytes;
         buffer->length -= bytes;
         stream += bytes;
         size -= bytes;
      }
      else if (port->format->es->audio.bits_per_sample == 32)
      {
         bytes = buffer->length;
         if (bytes > 2 * (unsigned int)size) bytes = 2 * size;
         vcos_assert(!(bytes&0x3));

         if (port->format->encoding == MMAL_ENCODING_PCM_FLOAT)
         {
            float *in = (float *)(buffer->data + buffer->offset);
            int16_t *out = (int16_t *)stream;
            for (i = 0; i < bytes / 4; i++)
            {
               if (*in >= 1.0) *out = 32767;
               else if (*in < -1.0) *out = -32768;
               else *out = *in * 32768.0;
               in++; out++;
            }
         }
         else if (port->format->encoding == MMAL_ENCODING_PCM_SIGNED)
         {
            int32_t *in = (int32_t *)(buffer->data + buffer->offset);
            int16_t *out = (int16_t *)stream;
            for (i = 0; i < bytes / 4; i++)
               *out++ = (*in++) >> 16;
         }
         buffer->offset += bytes;
         buffer->length -= bytes;
         stream += bytes / 2;
         size -= bytes / 2;
      }

      if (buffer->length)
      {
         /* We still have some data left for next time */
         mmal_queue_put_back(module->queue, buffer);
         continue;
      }

      /* Handle the EOS */
      if (buffer->flags & MMAL_BUFFER_HEADER_FLAG_EOS)
         mmal_event_eos_send(port);

      buffer->offset = 0;
      mmal_port_buffer_header_callback(port, buffer);
   }
}