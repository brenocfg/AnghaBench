#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ flags; int /*<<< orphan*/  queue; scalar_t__ user_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  sema; } ;
typedef  TYPE_1__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_2__ MMAL_CONNECTION_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ MMAL_CONNECTION_FLAG_DIRECT ; 
 int /*<<< orphan*/  graph_process_buffer (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void graph_connection_cb(MMAL_CONNECTION_T *connection)
{
   MMAL_GRAPH_PRIVATE_T *graph = (MMAL_GRAPH_PRIVATE_T *)connection->user_data;
   MMAL_BUFFER_HEADER_T *buffer;

   if (connection->flags == MMAL_CONNECTION_FLAG_DIRECT &&
       (buffer = mmal_queue_get(connection->queue)) != NULL)
   {
      graph_process_buffer(graph, connection, buffer);
      return;
   }

   vcos_semaphore_post(&graph->sema);
}