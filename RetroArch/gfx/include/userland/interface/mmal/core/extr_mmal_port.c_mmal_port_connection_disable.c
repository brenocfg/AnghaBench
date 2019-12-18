#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* core; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pool_for_connection; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_connection_disable(MMAL_PORT_T *port, MMAL_PORT_T *connected_port)
{
   MMAL_POOL_T *pool = port->priv->core->pool_for_connection ?
      port->priv->core->pool_for_connection : connected_port->priv->core->pool_for_connection;

   mmal_pool_destroy(pool);
   port->priv->core->pool_for_connection =
      connected_port->priv->core->pool_for_connection = NULL;
   return MMAL_SUCCESS;
}