#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct MMAL_PORT_USERDATA_T {int dummy; } ;
struct TYPE_4__ {struct MMAL_PORT_USERDATA_T* userdata; } ;
typedef  int /*<<< orphan*/  SVP_T ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_BH_CB_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_port_enable (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T svp_port_enable(SVP_T *svp, MMAL_PORT_T *port, MMAL_PORT_BH_CB_T cb)
{
   port->userdata = (struct MMAL_PORT_USERDATA_T *)svp;
   return mmal_port_enable(port, cb);
}