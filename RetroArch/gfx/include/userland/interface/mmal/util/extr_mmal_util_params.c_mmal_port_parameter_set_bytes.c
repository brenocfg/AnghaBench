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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {size_t size; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_2__ hdr; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_PARAMETER_BYTES_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 TYPE_1__* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ *,TYPE_2__*) ; 

MMAL_STATUS_T mmal_port_parameter_set_bytes(MMAL_PORT_T *port, uint32_t id,
   const uint8_t *data, unsigned int size)
{
   MMAL_PARAMETER_BYTES_T *param = 0;
   MMAL_STATUS_T status;
   size_t param_size = sizeof(param->hdr) + size;

   param = calloc(1, param_size);
   if (!param)
      return MMAL_ENOMEM;

   param->hdr.id = id;
   param->hdr.size = param_size;
   memcpy(param->data, data, size);
   status = mmal_port_parameter_set(port, &param->hdr);
   free(param);
   return status;
}