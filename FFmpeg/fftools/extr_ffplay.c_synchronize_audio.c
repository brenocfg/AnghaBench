#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double freq; } ;
struct TYPE_7__ {double audio_diff_cum; double audio_diff_avg_coef; scalar_t__ audio_diff_avg_count; scalar_t__ audio_diff_threshold; int /*<<< orphan*/  audio_clock; TYPE_1__ audio_src; int /*<<< orphan*/  audclk; } ;
typedef  TYPE_2__ VideoState ;

/* Variables and functions */
 scalar_t__ AUDIO_DIFF_AVG_NB ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 scalar_t__ AV_NOSYNC_THRESHOLD ; 
 scalar_t__ AV_SYNC_AUDIO_MASTER ; 
 int SAMPLE_CORRECTION_PERCENT_MAX ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,double,double,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fabs (double) ; 
 double get_clock (int /*<<< orphan*/ *) ; 
 double get_master_clock (TYPE_2__*) ; 
 scalar_t__ get_master_sync_type (TYPE_2__*) ; 
 int /*<<< orphan*/  isnan (double) ; 

__attribute__((used)) static int synchronize_audio(VideoState *is, int nb_samples)
{
    int wanted_nb_samples = nb_samples;

    /* if not master, then we try to remove or add samples to correct the clock */
    if (get_master_sync_type(is) != AV_SYNC_AUDIO_MASTER) {
        double diff, avg_diff;
        int min_nb_samples, max_nb_samples;

        diff = get_clock(&is->audclk) - get_master_clock(is);

        if (!isnan(diff) && fabs(diff) < AV_NOSYNC_THRESHOLD) {
            is->audio_diff_cum = diff + is->audio_diff_avg_coef * is->audio_diff_cum;
            if (is->audio_diff_avg_count < AUDIO_DIFF_AVG_NB) {
                /* not enough measures to have a correct estimate */
                is->audio_diff_avg_count++;
            } else {
                /* estimate the A-V difference */
                avg_diff = is->audio_diff_cum * (1.0 - is->audio_diff_avg_coef);

                if (fabs(avg_diff) >= is->audio_diff_threshold) {
                    wanted_nb_samples = nb_samples + (int)(diff * is->audio_src.freq);
                    min_nb_samples = ((nb_samples * (100 - SAMPLE_CORRECTION_PERCENT_MAX) / 100));
                    max_nb_samples = ((nb_samples * (100 + SAMPLE_CORRECTION_PERCENT_MAX) / 100));
                    wanted_nb_samples = av_clip(wanted_nb_samples, min_nb_samples, max_nb_samples);
                }
                av_log(NULL, AV_LOG_TRACE, "diff=%f adiff=%f sample_diff=%d apts=%0.3f %f\n",
                        diff, avg_diff, wanted_nb_samples - nb_samples,
                        is->audio_clock, is->audio_diff_threshold);
            }
        } else {
            /* too big difference : may be initial PTS errors, so
               reset A-V filter */
            is->audio_diff_avg_count = 0;
            is->audio_diff_cum       = 0;
        }
    }

    return wanted_nb_samples;
}