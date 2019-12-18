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
typedef  int /*<<< orphan*/  rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_VIDEO_SET_BLOCKING_STATE ; 
 int /*<<< orphan*/  RARCH_DRIVER_CTL_SET_REFRESH_RATE ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_ctl (int /*<<< orphan*/ ,float*) ; 
 scalar_t__ setting_generic_action_ok_default (int /*<<< orphan*/ *,int) ; 
 scalar_t__ video_monitor_fps_statistics (double*,double*,unsigned int*) ; 

__attribute__((used)) static int setting_action_ok_video_refresh_rate_auto(
      rarch_setting_t *setting, bool wraparound)
{
   double video_refresh_rate = 0.0;
   double deviation          = 0.0;
   unsigned sample_points    = 0;

   if (!setting)
      return -1;

   if (video_monitor_fps_statistics(&video_refresh_rate,
            &deviation, &sample_points))
   {
      float video_refresh_rate_float = (float)video_refresh_rate;
      driver_ctl(RARCH_DRIVER_CTL_SET_REFRESH_RATE, &video_refresh_rate_float);
      /* Incase refresh rate update forced non-block video. */
      command_event(CMD_EVENT_VIDEO_SET_BLOCKING_STATE, NULL);
   }

   if (setting_generic_action_ok_default(setting, wraparound) != 0)
      return -1;

   return 0;
}