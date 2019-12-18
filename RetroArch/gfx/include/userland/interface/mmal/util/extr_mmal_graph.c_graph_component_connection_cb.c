#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {scalar_t__ flags; int /*<<< orphan*/  queue; scalar_t__ user_data; } ;
struct TYPE_7__ {scalar_t__ module; } ;
typedef  int /*<<< orphan*/  MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_2__ MMAL_CONNECTION_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ MMAL_CONNECTION_FLAG_DIRECT ; 
 int /*<<< orphan*/  graph_process_buffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_component_action_trigger (TYPE_3__*) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void graph_component_connection_cb(MMAL_CONNECTION_T *connection)
{
   MMAL_COMPONENT_T *component = (MMAL_COMPONENT_T *)connection->user_data;
   MMAL_BUFFER_HEADER_T *buffer;

   if (connection->flags == MMAL_CONNECTION_FLAG_DIRECT &&
       (buffer = mmal_queue_get(connection->queue)) != NULL)
   {
      graph_process_buffer((MMAL_GRAPH_PRIVATE_T *)component->priv->module,
         connection, buffer);
      return;
   }

   mmal_component_action_trigger(component);
}