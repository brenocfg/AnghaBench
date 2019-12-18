#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ userdata; } ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;
typedef  int /*<<< orphan*/  MMALOMX_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmalomx_buffer_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmalomx_buffer_cb_io(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   mmalomx_buffer_return((MMALOMX_PORT_T *)port->userdata, buffer);
}