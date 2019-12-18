#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;

/* Variables and functions */
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ avcodec_port_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T avcodec_port_disable(MMAL_PORT_T *port)
{
   MMAL_STATUS_T status;

   /* Actions are prevented from running at that point so a flush
    * will return all buffers. */
   status = avcodec_port_flush(port);
   if(status != MMAL_SUCCESS)
      return status;

   return MMAL_SUCCESS;
}