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
struct TYPE_8__ {int /*<<< orphan*/  is_enabled; scalar_t__ index; scalar_t__ type; TYPE_1__* component; int /*<<< orphan*/  priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

void mmal_port_pool_destroy(MMAL_PORT_T *port, MMAL_POOL_T *pool)
{
   if (!port || !port->priv || !pool)
      return;

   LOG_TRACE("%s(%i:%i) port %p, pool %p", port->component->name,
             (int)port->type, (int)port->index, port, pool);

   if (!vcos_verify(!port->is_enabled))
   {
      LOG_ERROR("port %p, pool %p destroyed while port enabled", port, pool);
      mmal_port_disable(port);
   }

   mmal_pool_destroy(pool);
}