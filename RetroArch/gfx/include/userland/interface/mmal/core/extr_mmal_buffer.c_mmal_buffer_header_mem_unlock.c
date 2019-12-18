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
struct TYPE_6__ {TYPE_1__* priv; scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ payload_handle; } ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;
typedef  int /*<<< orphan*/  MEM_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (TYPE_2__*) ; 
 int /*<<< orphan*/  mem_unlock (int /*<<< orphan*/ ) ; 

void mmal_buffer_header_mem_unlock(MMAL_BUFFER_HEADER_T *header)
{
#ifdef __VIDEOCORE__
   mem_unlock((MEM_HANDLE_T)header->priv->payload_handle);
   header->data = header->priv->payload_handle;
#else
   MMAL_PARAM_UNUSED(header);
#endif
}