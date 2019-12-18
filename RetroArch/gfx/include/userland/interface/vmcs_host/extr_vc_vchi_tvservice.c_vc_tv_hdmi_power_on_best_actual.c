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
struct TYPE_3__ {void* in_3d; void* match_flags; void* scan_mode; void* frame_rate; void* height; void* width; } ;
typedef  TYPE_1__ TV_HDMI_ON_BEST_PARAM_T ;
typedef  int /*<<< orphan*/  HDMI_INTERLACED_T ;
typedef  int /*<<< orphan*/  EDID_MODE_MATCH_FLAG_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 void* VC_HTOV32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_TV_HDMI_ON_BEST ; 
 int tvservice_send_command (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc_tv_hdmi_power_on_best_actual(uint32_t width, uint32_t height, uint32_t frame_rate,
                                           HDMI_INTERLACED_T scan_mode, EDID_MODE_MATCH_FLAG_T match_flags,
                                           uint32_t in_3d) {
   TV_HDMI_ON_BEST_PARAM_T param;
   int success;

   vcos_log_trace("[%s]", VCOS_FUNCTION);
   param.width = VC_HTOV32(width);
   param.height = VC_HTOV32(height);
   param.frame_rate = VC_HTOV32(frame_rate);
   param.scan_mode = VC_HTOV32(scan_mode);
   param.match_flags = VC_HTOV32(match_flags);
   param.in_3d = VC_HTOV32(in_3d);

   success = tvservice_send_command( VC_TV_HDMI_ON_BEST, &param, sizeof(TV_HDMI_ON_BEST_PARAM_T), 1);
   return success;
}