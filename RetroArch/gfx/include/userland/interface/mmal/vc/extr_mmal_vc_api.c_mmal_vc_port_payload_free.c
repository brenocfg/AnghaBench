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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {scalar_t__ opaque_allocs; } ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {TYPE_3__* module; } ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_MODULE_T ;
typedef  int /*<<< orphan*/  MMAL_OPAQUE_IMAGE_HANDLE_T ;

/* Variables and functions */
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_vc_opaque_release (int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_vc_shm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmal_vc_port_payload_free(MMAL_PORT_T *port, uint8_t *payload)
{
   MMAL_PORT_MODULE_T *module = port->priv->module;

   if (module->opaque_allocs)
   {
      module->opaque_allocs--;
      mmal_vc_opaque_release((MMAL_OPAQUE_IMAGE_HANDLE_T)payload);
      return;
   }

   else if (mmal_vc_shm_free(payload) == MMAL_SUCCESS)
      return;

   /* We're dealing with conventional memory */
   vcos_free(payload);
}