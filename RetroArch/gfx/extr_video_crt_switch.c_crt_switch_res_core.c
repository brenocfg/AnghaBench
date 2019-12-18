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

/* Variables and functions */
 int crt_center_adjust ; 
 int /*<<< orphan*/  crt_check_first_run () ; 
 unsigned int crt_compute_dynamic_width (unsigned int) ; 
 int crt_index ; 
 int /*<<< orphan*/  crt_screen_setup_aspect (unsigned int,unsigned int) ; 
 int crt_tmp_center_adjust ; 
 scalar_t__ fly_aspect ; 
 unsigned int ra_core_height ; 
 float ra_core_hz ; 
 unsigned int ra_core_width ; 
 unsigned int ra_tmp_height ; 
 unsigned int ra_tmp_width ; 
 int /*<<< orphan*/  video_driver_apply_state_changes () ; 
 scalar_t__ video_driver_get_aspect_ratio () ; 
 int /*<<< orphan*/  video_driver_set_aspect_ratio_value (float) ; 

void crt_switch_res_core(unsigned width, unsigned height,
      float hz, unsigned crt_mode,
      int crt_switch_center_adjust, int monitor_index, bool dynamic)
{
   /* ra_core_hz float passed from within
    * video_driver_monitor_adjust_system_rates() */
   if (width == 4)
   {
      width = 320;
      height = 240;
   }

   ra_core_height = height;
   ra_core_hz     = hz;

   if (dynamic)
      ra_core_width = crt_compute_dynamic_width(width);
   else 
      ra_core_width  = width;

   crt_center_adjust = crt_switch_center_adjust;
   crt_index  = monitor_index;

   if (crt_mode == 2)
   {
      if (hz > 53)
         ra_core_hz = hz * 2;

      if (hz <= 53)
         ra_core_hz = 120.0f;
   }

   crt_check_first_run();

   /* Detect resolution change and switch */
   if (
      (ra_tmp_height != ra_core_height) ||
      (ra_core_width != ra_tmp_width) || (crt_center_adjust != crt_tmp_center_adjust)
      )
      crt_screen_setup_aspect(ra_core_width, ra_core_height);

   ra_tmp_height  = ra_core_height;
   ra_tmp_width   = ra_core_width;
    crt_tmp_center_adjust = crt_center_adjust;

   /* Check if aspect is correct, if not change */
   if (video_driver_get_aspect_ratio() != fly_aspect)
   {
      video_driver_set_aspect_ratio_value((float)fly_aspect);
      video_driver_apply_state_changes();
   }
}