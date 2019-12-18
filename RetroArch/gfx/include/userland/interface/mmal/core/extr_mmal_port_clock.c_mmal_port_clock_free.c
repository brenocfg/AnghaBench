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
typedef  int /*<<< orphan*/  MMAL_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_port_clock_teardown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_free (int /*<<< orphan*/ *) ; 

void mmal_port_clock_free(MMAL_PORT_T *port)
{
   mmal_port_clock_teardown(port);
   mmal_port_free(port);
}