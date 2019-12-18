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
struct TYPE_13__ {scalar_t__ stepping; } ;
struct TYPE_17__ {void* time_playback; scalar_t__ status; unsigned int connection_num; scalar_t__ video_out_port; scalar_t__ is_still_image; TYPE_1__ options; int /*<<< orphan*/  decoded_frames; TYPE_3__** connection; scalar_t__ stop; int /*<<< orphan*/  event; scalar_t__ audio_clock; scalar_t__ video_clock; int /*<<< orphan*/  uri; } ;
struct TYPE_16__ {scalar_t__ length; scalar_t__ cmd; } ;
struct TYPE_15__ {int flags; scalar_t__ out; scalar_t__ in; TYPE_2__* pool; int /*<<< orphan*/  queue; } ;
struct TYPE_14__ {int /*<<< orphan*/  queue; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_CONNECTION_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;
typedef  TYPE_5__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMALPLAY_STILL_IMAGE_PAUSE ; 
 int MMAL_CONNECTION_FLAG_TUNNELLING ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CLOCK_ACTIVE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  getchar () ; 
 int /*<<< orphan*/  mmal_port_parameter_set_boolean (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_send_buffer (scalar_t__,TYPE_4__*) ; 
 TYPE_4__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put_back (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ mmalplay_event_handle (TYPE_3__*,scalar_t__,TYPE_4__*) ; 
 void* vcos_getmicrosecs () ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_sleep (int /*<<< orphan*/ ) ; 

MMAL_STATUS_T mmalplay_play(MMALPLAY_T *ctx)
{
   MMAL_STATUS_T status = MMAL_SUCCESS;
   unsigned int i;

   LOG_TRACE("%p, %s", ctx, ctx->uri);

   ctx->time_playback = vcos_getmicrosecs();

   /* Start the clocks */
   if (ctx->video_clock)
      mmal_port_parameter_set_boolean(ctx->video_clock, MMAL_PARAMETER_CLOCK_ACTIVE, MMAL_TRUE);
   if (ctx->audio_clock)
      mmal_port_parameter_set_boolean(ctx->audio_clock, MMAL_PARAMETER_CLOCK_ACTIVE, MMAL_TRUE);

   while(1)
   {
      MMAL_BUFFER_HEADER_T *buffer;

      vcos_semaphore_wait(&ctx->event);
      if (ctx->stop || ctx->status != MMAL_SUCCESS)
      {
         status = ctx->status;
         break;
      }

      /* Loop through all the connections */
      for (i = 0; i < ctx->connection_num; i++)
      {
         MMAL_CONNECTION_T *connection = ctx->connection[i];

         if (connection->flags & MMAL_CONNECTION_FLAG_TUNNELLING)
            continue; /* Nothing else to do in tunnelling mode */

         /* Send any queued buffer to the next component */
         buffer = mmal_queue_get(connection->queue);
         while (buffer)
         {
            if (buffer->cmd)
            {
               status = mmalplay_event_handle(connection, connection->out, buffer);
               if (status != MMAL_SUCCESS)
                  goto error;
               buffer = mmal_queue_get(connection->queue);
               continue;
            }

            /* Code specific to handling of the video output port */
            if (connection->out == ctx->video_out_port)
            {
               if (buffer->length)
                  ctx->decoded_frames++;

               if (ctx->options.stepping)
                  getchar();
            }

            status = mmal_port_send_buffer(connection->in, buffer);
            if (status != MMAL_SUCCESS)
            {
               LOG_ERROR("mmal_port_send_buffer failed (%i)", status);
               mmal_queue_put_back(connection->queue, buffer);
               goto error;
            }
            buffer = mmal_queue_get(connection->queue);
         }

         /* Send empty buffers to the output port of the connection */
         buffer = connection->pool ? mmal_queue_get(connection->pool->queue) : NULL;
         while (buffer)
         {
            status = mmal_port_send_buffer(connection->out, buffer);
            if (status != MMAL_SUCCESS)
            {
               LOG_ERROR("mmal_port_send_buffer failed (%i)", status);
               mmal_queue_put_back(connection->pool->queue, buffer);
               goto error;
            }
            buffer = mmal_queue_get(connection->pool->queue);
         }
      }
   }

 error:
   ctx->time_playback = vcos_getmicrosecs() - ctx->time_playback;

   /* For still images we want to pause a bit once they are displayed */
   if (ctx->is_still_image && status == MMAL_SUCCESS)
      vcos_sleep(MMALPLAY_STILL_IMAGE_PAUSE);

   return status;
}