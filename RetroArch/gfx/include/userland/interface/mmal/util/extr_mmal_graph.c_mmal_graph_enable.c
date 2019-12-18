#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * name; void* userdata; } ;
struct TYPE_10__ {TYPE_2__* user_data; int /*<<< orphan*/  callback; } ;
struct TYPE_9__ {unsigned int component_num; unsigned int connection_num; int /*<<< orphan*/  sema; TYPE_3__** connection; TYPE_1__** component; void* event_cb_data; int /*<<< orphan*/  event_cb; int /*<<< orphan*/  thread; } ;
struct TYPE_8__ {TYPE_5__* control; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_EVENT_CB ;
typedef  TYPE_3__ MMAL_CONNECTION_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ MMAL_ENOSPC ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  graph_connection_cb ; 
 int /*<<< orphan*/  graph_control_cb ; 
 int /*<<< orphan*/  graph_stop_worker_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  graph_worker_thread ; 
 scalar_t__ mmal_connection_enable (TYPE_3__*) ; 
 scalar_t__ mmal_port_enable (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_thread_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

MMAL_STATUS_T mmal_graph_enable(MMAL_GRAPH_T *graph, MMAL_GRAPH_EVENT_CB cb, void *cb_data)
{
   MMAL_GRAPH_PRIVATE_T *private = (MMAL_GRAPH_PRIVATE_T *)graph;
   MMAL_STATUS_T status = MMAL_SUCCESS;
   unsigned int i;

   LOG_TRACE("graph: %p", graph);

   if (vcos_thread_create(&private->thread, "mmal graph thread", NULL,
                          graph_worker_thread, private) != VCOS_SUCCESS)
   {
      LOG_ERROR("failed to create worker thread %p", graph);
      return MMAL_ENOSPC;
   }

   private->event_cb = cb;
   private->event_cb_data = cb_data;

   /* Enable all control ports */
   for (i = 0; i < private->component_num; i++)
   {
      private->component[i]->control->userdata = (void *)private;
      status = mmal_port_enable(private->component[i]->control, graph_control_cb);
      if (status != MMAL_SUCCESS)
         LOG_ERROR("could not enable port %s", private->component[i]->control->name);
   }

   /* Enable all our connections */
   for (i = 0; i < private->connection_num; i++)
   {
      MMAL_CONNECTION_T *cx = private->connection[i];

      cx->callback = graph_connection_cb;
      cx->user_data = private;

      status = mmal_connection_enable(cx);
      if (status != MMAL_SUCCESS)
         goto error;
   }

   /* Trigger the worker thread to populate the output ports with empty buffers */
   vcos_semaphore_post(&private->sema);
   return status;

 error:
   graph_stop_worker_thread(private);
   return status;
}