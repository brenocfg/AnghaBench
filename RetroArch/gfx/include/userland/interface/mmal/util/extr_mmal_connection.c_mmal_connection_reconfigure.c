#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * format; } ;
struct TYPE_7__ {TYPE_2__* in; TYPE_2__* out; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_ES_FORMAT_T ;
typedef  TYPE_1__ MMAL_CONNECTION_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_connection_disable (TYPE_1__*) ; 
 scalar_t__ mmal_connection_enable (TYPE_1__*) ; 
 scalar_t__ mmal_format_full_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_format_commit (TYPE_2__*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_connection_reconfigure(MMAL_CONNECTION_T *connection, MMAL_ES_FORMAT_T *format)
{
   MMAL_STATUS_T status;
   LOG_TRACE("%p, %s", connection, connection->name);

   status = mmal_connection_disable(connection);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("connection couldn't be disabled");
      return status;
   }

   /* Set the new format for the output port */
   status = mmal_format_full_copy(connection->out->format, format);
   if (status == MMAL_SUCCESS)
      status = mmal_port_format_commit(connection->out);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("commit failed on port %s(%p) (%i)",
                connection->out->name, connection->out, status);
      return status;
   }

   /* Set the new format for the input port */
   status = mmal_format_full_copy(connection->in->format, connection->out->format);
   if (status == MMAL_SUCCESS)
      status = mmal_port_format_commit(connection->in);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("commit failed on port %s(%p) (%i)",
                connection->in->name, connection->in, status);
      return status;
   }

   /* Enable ports */
   status = mmal_connection_enable(connection);
   if (status)
   {
      LOG_ERROR("connection couldn't be enabled");
      return status;
   }

   return MMAL_SUCCESS;
}