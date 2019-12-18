#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  queue; } ;
struct TYPE_10__ {int is_enabled; void* time_enable; int flags; TYPE_6__* pool; int /*<<< orphan*/  name; TYPE_1__* out; TYPE_1__* in; } ;
struct TYPE_9__ {int capabilities; scalar_t__ type; void* buffer_size; void* buffer_num; void* buffer_size_recommended; void* buffer_num_recommended; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_CONNECTION_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int MMAL_CONNECTION_FLAG_KEEP_BUFFER_REQUIREMENTS ; 
 int MMAL_CONNECTION_FLAG_TUNNELLING ; 
 void* MMAL_MAX (void*,void*) ; 
 int MMAL_PORT_CAPABILITY_PASSTHROUGH ; 
 scalar_t__ MMAL_PORT_TYPE_CLOCK ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/ * mmal_connection_bh_clock_cb ; 
 int /*<<< orphan*/ * mmal_connection_bh_in_cb ; 
 int /*<<< orphan*/ * mmal_connection_bh_out_cb ; 
 scalar_t__ mmal_pool_resize (TYPE_6__*,void*,void*) ; 
 int /*<<< orphan*/  mmal_port_disable (TYPE_1__*) ; 
 scalar_t__ mmal_port_enable (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_send_buffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 void* vcos_getmicrosecs () ; 

MMAL_STATUS_T mmal_connection_enable(MMAL_CONNECTION_T *connection)
{
   MMAL_PORT_T *in = connection->in, *out = connection->out;
   uint32_t buffer_num, buffer_size;
   MMAL_STATUS_T status;

   LOG_TRACE("%p, %s", connection, connection->name);

   if (connection->is_enabled)
      return MMAL_SUCCESS;

   connection->time_enable = vcos_getmicrosecs();

   /* Override the buffer values with the recommended ones (the port probably knows best) */
   if (!(connection->flags & MMAL_CONNECTION_FLAG_KEEP_BUFFER_REQUIREMENTS))
   {
      if (out->buffer_num_recommended)
         out->buffer_num = out->buffer_num_recommended;
      if (out->buffer_size_recommended)
         out->buffer_size = out->buffer_size_recommended;
      if (in->buffer_num_recommended)
         in->buffer_num = in->buffer_num_recommended;
      if (in->buffer_size_recommended)
         in->buffer_size = in->buffer_size_recommended;
   }

   /* Special case for tunnelling */
   if (connection->flags & MMAL_CONNECTION_FLAG_TUNNELLING)
   {
      /* Enable port. No callback because the port is connected. Other end of the connection
       * will be enabled automatically. */
      status = mmal_port_enable(out, NULL);
      if (status)
         LOG_ERROR("output port couldn't be enabled");
      goto done;
   }

   /* Set the buffering properties on both ports */
   buffer_num = MMAL_MAX(out->buffer_num, in->buffer_num);
   buffer_size = MMAL_MAX(out->buffer_size, in->buffer_size);
   out->buffer_num = in->buffer_num = buffer_num;
   out->buffer_size = in->buffer_size = buffer_size;

   /* In pass-through mode there isn't any need to allocate memory */
   if (out->capabilities & MMAL_PORT_CAPABILITY_PASSTHROUGH)
      buffer_size = 0;

   /* Resize the output pool */
   status = mmal_pool_resize(connection->pool, buffer_num, buffer_size);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("couldn't resize pool");
      goto done;
   }

   /* Enable output port. The callback specified here is the function which
    * will be called when an empty buffer header comes back to the port. */
   status = mmal_port_enable(out, (out->type == MMAL_PORT_TYPE_CLOCK) ?
                             mmal_connection_bh_clock_cb : mmal_connection_bh_out_cb);
   if(status)
   {
      LOG_ERROR("output port couldn't be enabled");
      goto done;
   }

   /* Enable input port. The callback specified here is the function which
    * will be called when an empty buffer header comes back to the port. */
   status = mmal_port_enable(in, (in->type == MMAL_PORT_TYPE_CLOCK) ?
                             mmal_connection_bh_clock_cb : mmal_connection_bh_in_cb);
   if(status)
   {
      LOG_ERROR("input port couldn't be enabled");
      mmal_port_disable(out);
      goto done;
   }

   /* Clock ports need buffers to send clock updates, so
    * populate both connected clock ports */
   if ((out->type == MMAL_PORT_TYPE_CLOCK) && (in->type == MMAL_PORT_TYPE_CLOCK))
   {
      MMAL_BUFFER_HEADER_T *buffer = mmal_queue_get(connection->pool->queue);
      while (buffer)
      {
         mmal_port_send_buffer(out, buffer);
         buffer = mmal_queue_get(connection->pool->queue);
         if (buffer)
         {
            mmal_port_send_buffer(in, buffer);
            buffer = mmal_queue_get(connection->pool->queue);
         }
      }
   }

 done:
   connection->time_enable = vcos_getmicrosecs() - connection->time_enable;
   connection->is_enabled = status == MMAL_SUCCESS;
   return status;
}