#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ queue; scalar_t__ pool; int /*<<< orphan*/  name; int /*<<< orphan*/  out; scalar_t__ is_enabled; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_CONNECTION_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int MMAL_CONNECTION_FLAG_TUNNELLING ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_connection_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_pool_destroy (scalar_t__) ; 
 scalar_t__ mmal_port_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_connection_destroy_internal(MMAL_CONNECTION_T *connection)
{
   MMAL_STATUS_T status;

   if (connection->is_enabled)
   {
      status = mmal_connection_disable(connection);
      if (status != MMAL_SUCCESS)
         return status;
   }

   /* Special case for tunnelling */
   if (connection->flags & MMAL_CONNECTION_FLAG_TUNNELLING)
   {
      status = mmal_port_disconnect(connection->out);
      if (status != MMAL_SUCCESS)
         LOG_ERROR("connection %s could not be cleared", connection->name);
   }

   /* Cleanup resources */
   if (connection->pool)
      mmal_pool_destroy(connection->pool);
   if (connection->queue)
      mmal_queue_destroy(connection->queue);

   vcos_free(connection);
   return MMAL_SUCCESS;
}