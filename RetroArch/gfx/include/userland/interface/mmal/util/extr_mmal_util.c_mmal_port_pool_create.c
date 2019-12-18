#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  mmal_pool_allocator_free_t ;
typedef  int /*<<< orphan*/  mmal_pool_allocator_alloc_t ;
struct TYPE_6__ {scalar_t__ index; scalar_t__ type; TYPE_1__* component; int /*<<< orphan*/  priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int,int,TYPE_2__*,unsigned int,int) ; 
 int /*<<< orphan*/ * mmal_pool_create_with_allocator (unsigned int,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_payload_alloc ; 
 scalar_t__ mmal_port_payload_free ; 

MMAL_POOL_T *mmal_port_pool_create(MMAL_PORT_T *port, unsigned int headers, uint32_t payload_size)
{
   if (!port || !port->priv)
      return NULL;

   LOG_TRACE("%s(%i:%i) port %p, headers %u, size %i", port->component->name,
             (int)port->type, (int)port->index, port, headers, (int)payload_size);

   /* Create a pool and ask the port for some memory */
   return mmal_pool_create_with_allocator(headers, payload_size, (void *)port,
                                          (mmal_pool_allocator_alloc_t)mmal_port_payload_alloc,
                                          (mmal_pool_allocator_free_t)mmal_port_payload_free);
}