#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int buffer_size_min; int buffer_size; TYPE_1__* priv; int /*<<< orphan*/  buffer_num_min; int /*<<< orphan*/  buffer_num; TYPE_2__* format; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  pf_parameter_get; int /*<<< orphan*/  pf_parameter_set; int /*<<< orphan*/  pf_disable; int /*<<< orphan*/  pf_enable; } ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_ES_SPECIFIC_FORMAT_T ;
typedef  int /*<<< orphan*/  MMAL_ES_FORMAT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_CONTROL_PORT_BUFFERS_MIN ; 
 int /*<<< orphan*/  MMAL_ES_TYPE_CONTROL ; 
 int /*<<< orphan*/  mmal_component_disable_control_port ; 
 int /*<<< orphan*/  mmal_component_enable_control_port ; 
 int /*<<< orphan*/  mmal_component_parameter_get ; 
 int /*<<< orphan*/  mmal_component_parameter_set ; 

__attribute__((used)) static void mmal_component_init_control_port(MMAL_PORT_T *port)
{
   port->format->type = MMAL_ES_TYPE_CONTROL;
   port->buffer_num_min = MMAL_CONTROL_PORT_BUFFERS_MIN;
   port->buffer_num = port->buffer_num_min;
   port->buffer_size_min = sizeof(MMAL_ES_FORMAT_T) + sizeof(MMAL_ES_SPECIFIC_FORMAT_T);
   port->buffer_size = port->buffer_size_min;

   /* Default to generic handling */
   port->priv->pf_enable = mmal_component_enable_control_port;
   port->priv->pf_disable = mmal_component_disable_control_port;
   port->priv->pf_parameter_set = mmal_component_parameter_set;
   port->priv->pf_parameter_get = mmal_component_parameter_get;
   /* No pf_set_format - format of control port cannot be changed */
   /* No pf_send - buffers cannot be sent to control port */
}