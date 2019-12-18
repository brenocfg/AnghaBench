#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_19__ {void* userdata; } ;
struct TYPE_18__ {int /*<<< orphan*/ * input; int /*<<< orphan*/ * output; TYPE_5__* control; } ;
struct TYPE_17__ {int flags; int /*<<< orphan*/  in; int /*<<< orphan*/  queue; int /*<<< orphan*/  out; TYPE_1__* pool; void* callback; TYPE_14__* user_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  queue; } ;
struct TYPE_15__ {scalar_t__ status; int /*<<< orphan*/  semaphore; scalar_t__ eos; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_CONNECTION_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STATUS (scalar_t__,char*) ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CONTAINER_READER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_DECODER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER ; 
 int MMAL_CONNECTION_FLAG_TUNNELLING ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  bcm_host_init () ; 
 void* connection_callback ; 
 TYPE_14__ context ; 
 int /*<<< orphan*/  control_callback ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mmal_component_create (int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_3__*) ; 
 scalar_t__ mmal_component_enable (TYPE_3__*) ; 
 scalar_t__ mmal_connection_create (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_connection_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_connection_disable (TYPE_2__*) ; 
 scalar_t__ mmal_connection_enable (TYPE_2__*) ; 
 scalar_t__ mmal_port_enable (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_send_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_util_port_set_uri (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int vcos_countof (TYPE_2__**) ; 
 int /*<<< orphan*/  vcos_semaphore_create (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
   MMAL_STATUS_T status;
   MMAL_COMPONENT_T *reader = 0, *decoder = 0, *renderer = 0;
   MMAL_CONNECTION_T *connection[2] = {0};
   unsigned int i, count, connection_num = vcos_countof(connection);

   if (argc < 2)
   {
      fprintf(stderr, "invalid arguments\n");
      return -1;
   }

   bcm_host_init();

   vcos_semaphore_create(&context.semaphore, "example", 1);

   /* Create the components */
   status = mmal_component_create(MMAL_COMPONENT_DEFAULT_CONTAINER_READER, &reader);
   CHECK_STATUS(status, "failed to create reader");
   reader->control->userdata = (void *)&context;
   status = mmal_port_enable(reader->control, control_callback);
   CHECK_STATUS(status, "failed to enable control port");
   status = mmal_component_enable(reader);
   CHECK_STATUS(status, "failed to enable component");

   status = mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_DECODER, &decoder);
   CHECK_STATUS(status, "failed to create decoder");
   decoder->control->userdata = (void *)&context;
   status = mmal_port_enable(decoder->control, control_callback);
   CHECK_STATUS(status, "failed to enable control port");
   status = mmal_component_enable(decoder);
   CHECK_STATUS(status, "failed to enable component");

   status = mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER, &renderer);
   CHECK_STATUS(status, "failed to create renderer");
   renderer->control->userdata = (void *)&context;
   status = mmal_port_enable(renderer->control, control_callback);
   CHECK_STATUS(status, "failed to enable control port");
   status = mmal_component_enable(renderer);
   CHECK_STATUS(status, "failed to enable component");

   /* Configure the reader using the given URI */
   status = mmal_util_port_set_uri(reader->control, argv[1]);
   CHECK_STATUS(status, "failed to set uri");

   /* Create the connections between the components */
   status = mmal_connection_create(&connection[0], reader->output[0], decoder->input[0], 0);
   CHECK_STATUS(status, "failed to create connection between reader / decoder");
   connection[0]->user_data = &context;
   connection[0]->callback = connection_callback;
   status = mmal_connection_create(&connection[1], decoder->output[0], renderer->input[0], 0);
   CHECK_STATUS(status, "failed to create connection between decoder / renderer");
   connection[1]->user_data = &context;
   connection[1]->callback = connection_callback;

   /* Enable all our connections */
   for (i = connection_num; i; i--)
   {
      status = mmal_connection_enable(connection[i-1]);
      CHECK_STATUS(status, "failed to enable connection");
   }

   /* Start playback */
   fprintf(stderr, "start playback\n");

   /* This is the main processing loop */
   for (count = 0; count < 500; count++)
   {
      MMAL_BUFFER_HEADER_T *buffer;
      vcos_semaphore_wait(&context.semaphore);

      /* Check for errors */
      status = context.status;
      CHECK_STATUS(status, "error during playback");

      /* Check for end of stream */
      if (context.eos)
         break;

      /* Handle buffers for all our connections */
      for (i = 0; i < connection_num; i++)
      {
         if (connection[i]->flags & MMAL_CONNECTION_FLAG_TUNNELLING)
            continue; /* Nothing else to do in tunnelling mode */

         /* Send empty buffers to the output port of the connection */
         while ((buffer = mmal_queue_get(connection[i]->pool->queue)) != NULL)
         {
            status = mmal_port_send_buffer(connection[i]->out, buffer);
            CHECK_STATUS(status, "failed to send buffer");
         }

         /* Send any queued buffer to the next component */
         while ((buffer = mmal_queue_get(connection[i]->queue)) != NULL)
         {
            status = mmal_port_send_buffer(connection[i]->in, buffer);
            CHECK_STATUS(status, "failed to send buffer");
         }
      }
   }

   /* Stop everything */
   fprintf(stderr, "stop playback\n");
   for (i = 0; i < connection_num; i++)
   {
      mmal_connection_disable(connection[i]);
   }

 error:
   /* Cleanup everything */
   for (i = 0; i < connection_num; i++)
   {
      if (connection[i])
         mmal_connection_destroy(connection[i]);
   }
   if (reader)
      mmal_component_destroy(reader);
   if (decoder)
      mmal_component_destroy(decoder);
   if (renderer)
      mmal_component_destroy(renderer);

   vcos_semaphore_delete(&context.semaphore);
   return status == MMAL_SUCCESS ? 0 : -1;
}