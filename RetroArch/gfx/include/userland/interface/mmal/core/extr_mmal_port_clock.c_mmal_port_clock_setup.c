#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* user_data; } ;
struct TYPE_9__ {TYPE_5__* clock; int /*<<< orphan*/  queue; int /*<<< orphan*/  event_cb; } ;
struct TYPE_8__ {int buffer_size; int buffer_size_min; int /*<<< orphan*/  capabilities; TYPE_1__* priv; void* buffer_num_recommended; void* buffer_num_min; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  pf_payload_free; int /*<<< orphan*/  pf_payload_alloc; int /*<<< orphan*/  pf_connect; int /*<<< orphan*/  pf_parameter_get; int /*<<< orphan*/  pf_parameter_set; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_send; int /*<<< orphan*/  pf_disable; int /*<<< orphan*/  pf_enable; int /*<<< orphan*/  pf_set_format; TYPE_3__* clock; scalar_t__ module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_CLOCK_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_CLOCK_EVENT_CB ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_PORT_CAPABILITY_ALLOCATION ; 
 void* MMAL_PORT_CLOCK_BUFFERS_MIN ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_clock_create (TYPE_5__**) ; 
 int /*<<< orphan*/  mmal_clock_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_port_clock_connect ; 
 int /*<<< orphan*/  mmal_port_clock_disable ; 
 int /*<<< orphan*/  mmal_port_clock_enable ; 
 int /*<<< orphan*/  mmal_port_clock_flush ; 
 int /*<<< orphan*/  mmal_port_clock_parameter_get ; 
 int /*<<< orphan*/  mmal_port_clock_parameter_set ; 
 int /*<<< orphan*/  mmal_port_clock_payload_alloc ; 
 int /*<<< orphan*/  mmal_port_clock_payload_free ; 
 int /*<<< orphan*/  mmal_port_clock_send ; 
 int /*<<< orphan*/  mmal_port_clock_set_format ; 
 int /*<<< orphan*/  mmal_queue_create () ; 
 int /*<<< orphan*/  mmal_status_to_string (scalar_t__) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_clock_setup(MMAL_PORT_T *port, unsigned int extra_size,
                                           MMAL_PORT_CLOCK_EVENT_CB event_cb)
{
   MMAL_STATUS_T status;

   port->priv->clock = (MMAL_PORT_CLOCK_T*)((char*)(port->priv->module) + extra_size);

   status = mmal_clock_create(&port->priv->clock->clock);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("failed to create clock module on port %s (%s)",
                port->name, mmal_status_to_string(status));
      return status;
   }
   port->priv->clock->clock->user_data = port;

   port->buffer_size = sizeof(MMAL_CLOCK_EVENT_T);
   port->buffer_size_min = sizeof(MMAL_CLOCK_EVENT_T);
   port->buffer_num_min = MMAL_PORT_CLOCK_BUFFERS_MIN;
   port->buffer_num_recommended = MMAL_PORT_CLOCK_BUFFERS_MIN;

   port->priv->clock->event_cb = event_cb;
   port->priv->clock->queue = mmal_queue_create();
   if (!port->priv->clock->queue)
   {
      mmal_clock_destroy(port->priv->clock->clock);
      return MMAL_ENOMEM;
   }

   port->priv->pf_set_format = mmal_port_clock_set_format;
   port->priv->pf_enable = mmal_port_clock_enable;
   port->priv->pf_disable = mmal_port_clock_disable;
   port->priv->pf_send = mmal_port_clock_send;
   port->priv->pf_flush = mmal_port_clock_flush;
   port->priv->pf_parameter_set = mmal_port_clock_parameter_set;
   port->priv->pf_parameter_get = mmal_port_clock_parameter_get;
   port->priv->pf_connect = mmal_port_clock_connect;
#ifdef __VIDEOCORE__
   port->priv->pf_payload_alloc = mmal_port_clock_payload_alloc;
   port->priv->pf_payload_free = mmal_port_clock_payload_free;
   port->capabilities = MMAL_PORT_CAPABILITY_ALLOCATION;
#endif

   return status;
}