#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int is_enabled; void* time_disable; int flags; TYPE_1__* pool; int /*<<< orphan*/  queue; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ headers_num; int /*<<< orphan*/  queue; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_CONNECTION_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int MMAL_CONNECTION_FLAG_TUNNELLING ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_buffer_header_release (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 void* vcos_getmicrosecs () ; 

MMAL_STATUS_T mmal_connection_disable(MMAL_CONNECTION_T *connection)
{
   MMAL_STATUS_T status;
   MMAL_BUFFER_HEADER_T *buffer;

   LOG_TRACE("%p, %s", connection, connection->name);

   if (!connection->is_enabled)
      return MMAL_SUCCESS;

   connection->time_disable = vcos_getmicrosecs();

   /* Special case for tunnelling */
   if (connection->flags & MMAL_CONNECTION_FLAG_TUNNELLING)
   {
      /* Disable port. Other end of the connection will be disabled automatically. */
      status = mmal_port_disable(connection->out);
      if (status)
         LOG_ERROR("output port couldn't be disabled");
      goto done;
   }

   /* Disable input port. */
   status = mmal_port_disable(connection->in);
   if(status)
   {
      LOG_ERROR("input port couldn't be disabled");
      goto done;
   }

   /* Disable output port */
   status = mmal_port_disable(connection->out);
   if(status)
   {
      LOG_ERROR("output port couldn't be disabled");
      goto done;
   }

   /* Flush the queue */
   buffer = mmal_queue_get(connection->queue);
   while (buffer)
   {
      mmal_buffer_header_release(buffer);
      buffer = mmal_queue_get(connection->queue);
   }
   vcos_assert(mmal_queue_length(connection->pool->queue) == connection->pool->headers_num);

 done:
   connection->time_disable = vcos_getmicrosecs() - connection->time_disable;
   connection->is_enabled = !(status == MMAL_SUCCESS);
   return status;
}