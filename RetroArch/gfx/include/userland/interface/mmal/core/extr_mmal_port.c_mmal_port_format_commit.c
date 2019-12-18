#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  encoding_string ;
struct TYPE_17__ {scalar_t__ type; scalar_t__ buffer_size; scalar_t__ buffer_size_min; scalar_t__ buffer_num; scalar_t__ buffer_num_min; TYPE_4__* component; TYPE_3__* priv; int /*<<< orphan*/  name; TYPE_2__* format; scalar_t__ index; } ;
struct TYPE_16__ {unsigned int output_num; TYPE_5__** output; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* pf_set_format ) (TYPE_5__*) ;TYPE_1__* core; } ;
struct TYPE_14__ {scalar_t__ encoding; scalar_t__ type; } ;
struct TYPE_13__ {TYPE_2__* format_ptr_copy; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_PORT (TYPE_5__*) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,TYPE_5__*,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int,int,TYPE_5__*,int,char*) ; 
 int /*<<< orphan*/  MMAL_EFAULT ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 int /*<<< orphan*/  UNLOCK_PORT (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_port_name_update (TYPE_5__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

MMAL_STATUS_T mmal_port_format_commit(MMAL_PORT_T *port)
{
   MMAL_STATUS_T status;
   char encoding_string[16];

   if (!port || !port->priv)
   {
      LOG_ERROR("invalid port (%p/%p)", port, port ? port->priv : NULL);
      return MMAL_EINVAL;
   }

   if (port->format != port->priv->core->format_ptr_copy)
   {
      LOG_ERROR("%s: port format has been overwritten, resetting %p to %p",
            port->name, port->format, port->priv->core->format_ptr_copy);
      port->format = port->priv->core->format_ptr_copy;
      return MMAL_EFAULT;
   }

   if (port->format->encoding == 0)
      snprintf(encoding_string, sizeof(encoding_string), "<NO-FORMAT>");
   else
      snprintf(encoding_string, sizeof(encoding_string), "%4.4s", (char*)&port->format->encoding);

   LOG_TRACE("%s(%i:%i) port %p format %i:%s",
             port->component->name, (int)port->type, (int)port->index, port,
             (int)port->format->type, encoding_string);

   if (!port->priv->pf_set_format)
   {
      LOG_ERROR("%s: no component implementation", port->name);
      return MMAL_ENOSYS;
   }

   LOCK_PORT(port);
   status = port->priv->pf_set_format(port);
   mmal_port_name_update(port);

   /* Make sure the buffer size / num are sensible */
   if (port->buffer_size < port->buffer_size_min)
      port->buffer_size = port->buffer_size_min;
   if (port->buffer_num < port->buffer_num_min)
      port->buffer_num = port->buffer_num_min;
   /* The output port settings might have changed */
   if (port->type == MMAL_PORT_TYPE_INPUT)
   {
      MMAL_PORT_T **ports = port->component->output;
      unsigned int i;

      for (i = 0; i < port->component->output_num; i++)
      {
         if (ports[i]->buffer_size < ports[i]->buffer_size_min)
            ports[i]->buffer_size = ports[i]->buffer_size_min;
         if (ports[i]->buffer_num < ports[i]->buffer_num_min)
            ports[i]->buffer_num = ports[i]->buffer_num_min;
      }
   }

   UNLOCK_PORT(port);
   return status;
}