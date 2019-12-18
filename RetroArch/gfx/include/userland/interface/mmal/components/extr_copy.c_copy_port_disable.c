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
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  copy_port_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T copy_port_disable(MMAL_PORT_T *port)
{
   /* We just need to flush our internal queue */
   return copy_port_flush(port);
}