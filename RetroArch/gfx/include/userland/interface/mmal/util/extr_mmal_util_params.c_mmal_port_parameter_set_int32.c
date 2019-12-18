#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_PARAMETER_INT32_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_port_parameter_set_int32(MMAL_PORT_T *port, uint32_t id, int32_t value)
{
   MMAL_PARAMETER_INT32_T param = {{id, sizeof(param)}, value};
   return mmal_port_parameter_set(port, &param.hdr);
}