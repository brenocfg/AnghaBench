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
struct TYPE_3__ {int /*<<< orphan*/  prefs; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int gint ;

/* Variables and functions */
 float ghb_settings_combo_double (int /*<<< orphan*/ ,char*) ; 
 int ghb_settings_video_encoder_codec (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hb_video_quality_get_limits (int,float*,float*,float*,int*) ; 

void
ghb_vquality_range(
    signal_user_data_t *ud,
    float *min,
    float *max,
    float *step,
    float *page,
    gint *digits,
    int *direction)
{
    float min_step;
    gint vcodec;
    vcodec = ghb_settings_video_encoder_codec(ud->settings, "VideoEncoder");

    *page = 10;
    *digits = 0;
    hb_video_quality_get_limits(vcodec, min, max, &min_step, direction);
    *step = ghb_settings_combo_double(ud->prefs, "VideoQualityGranularity");

    if (*step < min_step)
        *step = min_step;

    if ((int)(*step * 100) % 10 != 0)
        *digits = 2;
    else if ((int)(*step * 10) % 10 != 0)
        *digits = 1;
}