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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  param ;
struct TYPE_3__ {int /*<<< orphan*/  in_3d; } ;
typedef  TYPE_1__ TV_HDMI_ON_PREFERRED_PARAM_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VC_HTOV32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_TV_HDMI_ON_PREFERRED ; 
 int tvservice_send_command (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc_tv_hdmi_power_on_preferred_actual(uint32_t in_3d) {
   TV_HDMI_ON_PREFERRED_PARAM_T param;
   int success;

   vcos_log_trace("[%s]", VCOS_FUNCTION);
   param.in_3d = VC_HTOV32(in_3d);

   success = tvservice_send_command( VC_TV_HDMI_ON_PREFERRED, &param, sizeof(param), 1);
   return success;
}