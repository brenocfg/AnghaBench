#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * input; int /*<<< orphan*/ * output; int /*<<< orphan*/  control; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_T ;
typedef  TYPE_1__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STATUS (scalar_t__,char*) ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CONTAINER_READER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_DECODER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  bcm_host_init () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmal_component_release (TYPE_1__*) ; 
 scalar_t__ mmal_graph_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_graph_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_graph_disable (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_graph_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_graph_new_component (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ mmal_graph_new_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_util_port_set_uri (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
   MMAL_STATUS_T status;
   MMAL_GRAPH_T *graph = 0;
   MMAL_COMPONENT_T *reader = 0, *decoder = 0, *renderer = 0;

   if (argc < 2)
   {
      fprintf(stderr, "invalid arguments\n");
      return -1;
   }

   bcm_host_init();

   /* Create the graph */
   status = mmal_graph_create(&graph, 0);
   CHECK_STATUS(status, "failed to create graph");

   /* Add the components */
   status = mmal_graph_new_component(graph, MMAL_COMPONENT_DEFAULT_CONTAINER_READER, &reader);
   CHECK_STATUS(status, "failed to create reader");

   status = mmal_graph_new_component(graph, MMAL_COMPONENT_DEFAULT_VIDEO_DECODER, &decoder);
   CHECK_STATUS(status, "failed to create decoder");

   status = mmal_graph_new_component(graph, MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER, &renderer);
   CHECK_STATUS(status, "failed to create renderer");

   /* Configure the reader using the given URI */
   status = mmal_util_port_set_uri(reader->control, argv[1]);
   CHECK_STATUS(status, "failed to set uri");

   /* connect them up - this propagates port settings from outputs to inputs */
   status = mmal_graph_new_connection(graph, reader->output[0], decoder->input[0], 0, NULL);
   CHECK_STATUS(status, "failed to connect reader to decoder");
   status = mmal_graph_new_connection(graph, decoder->output[0], renderer->input[0], 0, NULL);
   CHECK_STATUS(status, "failed to connect decoder to renderer");

   /* Start playback */
   fprintf(stderr, "start playback\n");
   status = mmal_graph_enable(graph, NULL, NULL);
   CHECK_STATUS(status, "failed to enable graph");

   sleep(5);

   /* Stop everything */
   fprintf(stderr, "stop playback\n");
   mmal_graph_disable(graph);

 error:
   /* Cleanup everything */
   if (reader)
      mmal_component_release(reader);
   if (decoder)
      mmal_component_release(decoder);
   if (renderer)
      mmal_component_release(renderer);
   if (graph)
      mmal_graph_destroy(graph);

   return status == MMAL_SUCCESS ? 0 : -1;
}