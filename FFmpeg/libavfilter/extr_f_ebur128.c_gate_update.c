#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct integrator {double sum_kept_powers; double nb_kept_powers; double rel_threshold; TYPE_1__* histogram; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIST_POS (double) ; 
 scalar_t__ HIST_SIZE ; 
 double LOUDNESS (double) ; 
 int av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gate_update(struct integrator *integ, double power,
                       double loudness, int gate_thres)
{
    int ipower;
    double relative_threshold;
    int gate_hist_pos;

    /* update powers histograms by incrementing current power count */
    ipower = av_clip(HIST_POS(loudness), 0, HIST_SIZE - 1);
    integ->histogram[ipower].count++;

    /* compute relative threshold and get its position in the histogram */
    integ->sum_kept_powers += power;
    integ->nb_kept_powers++;
    relative_threshold = integ->sum_kept_powers / integ->nb_kept_powers;
    if (!relative_threshold)
        relative_threshold = 1e-12;
    integ->rel_threshold = LOUDNESS(relative_threshold) + gate_thres;
    gate_hist_pos = av_clip(HIST_POS(integ->rel_threshold), 0, HIST_SIZE - 1);

    return gate_hist_pos;
}