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
struct TYPE_3__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_PARAMETER_CAMERA_STC_MODE_T ;
typedef  int /*<<< orphan*/  MMAL_CAMERA_STC_MODE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_USE_STC ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_util_camera_use_stc_timestamp(MMAL_PORT_T *port, MMAL_CAMERA_STC_MODE_T mode)
{
   MMAL_PARAMETER_CAMERA_STC_MODE_T param =
      {{MMAL_PARAMETER_USE_STC, sizeof(MMAL_PARAMETER_CAMERA_STC_MODE_T)},mode};
   return mmal_port_parameter_set(port, &param.hdr);
}