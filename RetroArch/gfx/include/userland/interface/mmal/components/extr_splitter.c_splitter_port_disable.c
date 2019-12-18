#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; int index; TYPE_3__* component; } ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {TYPE_1__* module; } ;
struct TYPE_7__ {int enabled_flags; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;

/* Variables and functions */
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 int /*<<< orphan*/  splitter_port_flush (TYPE_4__*) ; 

__attribute__((used)) static MMAL_STATUS_T splitter_port_disable(MMAL_PORT_T *port)
{
   if (port->type == MMAL_PORT_TYPE_OUTPUT)
      port->component->priv->module->enabled_flags &= ~(1<<port->index);

   /* We just need to flush our internal queue */
   return splitter_port_flush(port);
}