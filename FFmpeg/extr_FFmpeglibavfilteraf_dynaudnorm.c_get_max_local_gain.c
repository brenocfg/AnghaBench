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
struct TYPE_3__ {double peak_value; double target_rms; int /*<<< orphan*/  max_amplification; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 double DBL_EPSILON ; 
 double DBL_MAX ; 
 int /*<<< orphan*/  FFMIN (double const,double const) ; 
 double bound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double compute_frame_rms (int /*<<< orphan*/ *,int) ; 
 double find_peak_magnitude (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static double get_max_local_gain(DynamicAudioNormalizerContext *s, AVFrame *frame,
                                 int channel)
{
    const double maximum_gain = s->peak_value / find_peak_magnitude(frame, channel);
    const double rms_gain = s->target_rms > DBL_EPSILON ? (s->target_rms / compute_frame_rms(frame, channel)) : DBL_MAX;
    return bound(s->max_amplification, FFMIN(maximum_gain, rms_gain));
}