#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  param ;
struct TYPE_7__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; TYPE_2__ member_1; TYPE_1__ member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_RATIONAL_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_PARAMETER_RATIONAL_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_port_parameter_set_rational(MMAL_PORT_T *port, uint32_t id, MMAL_RATIONAL_T value)
{
   MMAL_PARAMETER_RATIONAL_T param = {{id, sizeof(param)}, {value.num, value.den}};
   return mmal_port_parameter_set(port, &param.hdr);
}