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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,double) ; 
 double video_driver_get_refresh_rate () ; 

__attribute__((used)) static void
setting_get_string_representation_st_float_video_refresh_rate_polled(
      rarch_setting_t *setting, char *s, size_t len)
{
    snprintf(s, len, "%.3f Hz", video_driver_get_refresh_rate());
}