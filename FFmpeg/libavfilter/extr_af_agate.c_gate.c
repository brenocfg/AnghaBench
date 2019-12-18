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
struct TYPE_7__ {int channels; } ;
struct TYPE_6__ {double makeup; double attack_coeff; double release_coeff; int link; double lin_slope; double lin_knee_start; double lin_knee_stop; scalar_t__ mode; int /*<<< orphan*/  range; int /*<<< orphan*/  knee_stop; int /*<<< orphan*/  knee_start; int /*<<< orphan*/  knee; int /*<<< orphan*/  thres; int /*<<< orphan*/  ratio; scalar_t__ detection; } ;
typedef  TYPE_1__ AudioGateContext ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 double FFMAX (double,double) ; 
 double fabs (double const) ; 
 double output_gain (double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void gate(AudioGateContext *s,
                 const double *src, double *dst, const double *scsrc,
                 int nb_samples, double level_in, double level_sc,
                 AVFilterLink *inlink, AVFilterLink *sclink)
{
    const double makeup = s->makeup;
    const double attack_coeff = s->attack_coeff;
    const double release_coeff = s->release_coeff;
    int n, c;

    for (n = 0; n < nb_samples; n++, src += inlink->channels, dst += inlink->channels, scsrc += sclink->channels) {
        double abs_sample = fabs(scsrc[0] * level_sc), gain = 1.0;
        int detected;

        if (s->link == 1) {
            for (c = 1; c < sclink->channels; c++)
                abs_sample = FFMAX(fabs(scsrc[c] * level_sc), abs_sample);
        } else {
            for (c = 1; c < sclink->channels; c++)
                abs_sample += fabs(scsrc[c] * level_sc);

            abs_sample /= sclink->channels;
        }

        if (s->detection)
            abs_sample *= abs_sample;

        s->lin_slope += (abs_sample - s->lin_slope) * (abs_sample > s->lin_slope ? attack_coeff : release_coeff);

        if (s->mode)
            detected = s->lin_slope > s->lin_knee_start;
        else
            detected = s->lin_slope < s->lin_knee_stop;

        if (s->lin_slope > 0.0 && detected)
            gain = output_gain(s->lin_slope, s->ratio, s->thres,
                               s->knee, s->knee_start, s->knee_stop,
                               s->range, s->mode);

        for (c = 0; c < inlink->channels; c++)
            dst[c] = src[c] * level_in * gain * makeup;
    }
}