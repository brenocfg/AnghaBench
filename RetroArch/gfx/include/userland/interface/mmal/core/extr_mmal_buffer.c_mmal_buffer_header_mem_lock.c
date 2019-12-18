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
struct TYPE_6__ {int /*<<< orphan*/ * data; TYPE_1__* priv; } ;
struct TYPE_5__ {void* payload_handle; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;
typedef  int /*<<< orphan*/  MEM_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (TYPE_2__*) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/ * mem_lock (int /*<<< orphan*/ ) ; 

MMAL_STATUS_T mmal_buffer_header_mem_lock(MMAL_BUFFER_HEADER_T *header)
{
#ifdef __VIDEOCORE__
   uint8_t *data = mem_lock((MEM_HANDLE_T)header->data);
   if (!data)
      return MMAL_EINVAL;
   header->priv->payload_handle = (void *)header->data;
   header->data = data;
#else
   MMAL_PARAM_UNUSED(header);
#endif

   return MMAL_SUCCESS;
}