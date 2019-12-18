#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ length; scalar_t__ offset; int /*<<< orphan*/  data; scalar_t__ cmd; } ;
struct TYPE_18__ {TYPE_2__* priv; int /*<<< orphan*/  name; scalar_t__ index; scalar_t__ type; TYPE_3__* component; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {TYPE_1__* core; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* buffer_header_callback ) (TYPE_4__*,TYPE_5__*) ;} ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  TYPE_5__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ IN_TRANSIT_COUNT (TYPE_4__*) ; 
 int /*<<< orphan*/  IN_TRANSIT_DECREMENT (TYPE_4__*) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int,int,TYPE_4__*,TYPE_5__*,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ MMAL_COLLECT_PORT_STATS_ENABLED ; 
 int /*<<< orphan*/  MMAL_CORE_STATS_TX ; 
 int /*<<< orphan*/  mmal_port_update_port_stats (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

void mmal_port_buffer_header_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
#ifdef ENABLE_MMAL_EXTRA_LOGGING
   LOG_TRACE("%s(%i:%i) port %p, buffer %p (%i,%p,%i,%i)",
             port->component->name, (int)port->type, (int)port->index, port, buffer,
             buffer ? (int)buffer->cmd : 0, buffer ? buffer->data : 0,
             buffer ? (int)buffer->offset : 0, buffer ? (int)buffer->length : 0);
#endif

   if (!vcos_verify(IN_TRANSIT_COUNT(port) >= 0))
      LOG_ERROR("%s: buffer headers in transit < 0 (%d)", port->name, (int)IN_TRANSIT_COUNT(port));

   if (MMAL_COLLECT_PORT_STATS_ENABLED)
   {
      mmal_port_update_port_stats(port, MMAL_CORE_STATS_TX);
   }

   port->priv->core->buffer_header_callback(port, buffer);

   IN_TRANSIT_DECREMENT(port);
}