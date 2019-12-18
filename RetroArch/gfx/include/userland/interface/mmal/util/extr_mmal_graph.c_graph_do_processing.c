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
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {scalar_t__ is_enabled; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  queue; TYPE_1__* pool; TYPE_4__* out; } ;
struct TYPE_9__ {unsigned int connection_current; unsigned int connection_num; TYPE_3__** connection; } ;
struct TYPE_8__ {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_3__ MMAL_CONNECTION_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int MMAL_CONNECTION_FLAG_DIRECT ; 
 int MMAL_CONNECTION_FLAG_TUNNELLING ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ PROCESSING_TIME_MAX ; 
 int /*<<< orphan*/  graph_process_buffer (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_send_buffer (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_getmicrosecs64 () ; 

__attribute__((used)) static MMAL_BOOL_T graph_do_processing(MMAL_GRAPH_PRIVATE_T *graph_private)
{
   MMAL_BUFFER_HEADER_T *buffer;
   MMAL_BOOL_T run_again = 0;
   MMAL_STATUS_T status;
   unsigned int i, j;

   /* Process all the empty buffers first */
   for (i = 0, j = graph_private->connection_current;
        i < graph_private->connection_num; i++, j++)
   {
      MMAL_CONNECTION_T *connection =
         graph_private->connection[j%graph_private->connection_num];

      if ((connection->flags & MMAL_CONNECTION_FLAG_TUNNELLING) ||
          !connection->pool)
         continue; /* Nothing else to do in tunnelling mode */

      /* Send empty buffers to the output port of the connection */
      while ((buffer = mmal_queue_get(connection->pool->queue)) != NULL)
      {
         run_again = 1;

         status = mmal_port_send_buffer(connection->out, buffer);
         if (status != MMAL_SUCCESS)
         {
            if (connection->out->is_enabled)
               LOG_ERROR("mmal_port_send_buffer failed (%i)", status);
            mmal_queue_put_back(connection->pool->queue, buffer);
            run_again = 0;
            break;
         }
      }
   }

   /* Loop through all the connections */
   for (i = 0, j = graph_private->connection_current++;
        i < graph_private->connection_num; i++, j++)
   {
      MMAL_CONNECTION_T *connection =
         graph_private->connection[j%graph_private->connection_num];
      int64_t duration = vcos_getmicrosecs64();

      if (connection->flags & MMAL_CONNECTION_FLAG_TUNNELLING)
         continue; /* Nothing else to do in tunnelling mode */
      if (connection->flags & MMAL_CONNECTION_FLAG_DIRECT)
         continue; /* Nothing else to do in direct mode */

      /* Send any queued buffer to the next component.
       * We also make sure no connection can starve the others by
       * having a timeout. */
      while (vcos_getmicrosecs64() - duration < PROCESSING_TIME_MAX &&
             (buffer = mmal_queue_get(connection->queue)) != NULL)
      {
         run_again = 1;

         graph_process_buffer(graph_private, connection, buffer);
      }
   }

   return run_again;
}