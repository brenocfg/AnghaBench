#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nb_channels; TYPE_1__* chstats; } ;
struct TYPE_4__ {int imask; scalar_t__ nb_denormals; scalar_t__ nb_infs; scalar_t__ nb_nans; scalar_t__ nb_samples; scalar_t__ zero_runs; scalar_t__ max_count; scalar_t__ min_count; scalar_t__ mask; scalar_t__ diff1_sum_x2; scalar_t__ diff1_sum; scalar_t__ max_runs; scalar_t__ min_runs; scalar_t__ max_run; scalar_t__ min_run; scalar_t__ avg_sigma_x2; scalar_t__ sigma_x2; scalar_t__ sigma_x; void* max_diff; void* min_diff; void* min_non_zero; void* max_sigma_x2; void* nmax; void* max; void* min_sigma_x2; void* nmin; void* min; } ;
typedef  TYPE_1__ ChannelStats ;
typedef  TYPE_2__ AudioStatsContext ;

/* Variables and functions */
 void* DBL_MAX ; 
 void* DBL_MIN ; 

__attribute__((used)) static void reset_stats(AudioStatsContext *s)
{
    int c;

    for (c = 0; c < s->nb_channels; c++) {
        ChannelStats *p = &s->chstats[c];

        p->min = p->nmin = p->min_sigma_x2 = DBL_MAX;
        p->max = p->nmax = p->max_sigma_x2 = DBL_MIN;
        p->min_non_zero = DBL_MAX;
        p->min_diff = DBL_MAX;
        p->max_diff = DBL_MIN;
        p->sigma_x = 0;
        p->sigma_x2 = 0;
        p->avg_sigma_x2 = 0;
        p->min_run = 0;
        p->max_run = 0;
        p->min_runs = 0;
        p->max_runs = 0;
        p->diff1_sum = 0;
        p->diff1_sum_x2 = 0;
        p->mask = 0;
        p->imask = 0xFFFFFFFFFFFFFFFF;
        p->min_count = 0;
        p->max_count = 0;
        p->zero_runs = 0;
        p->nb_samples = 0;
        p->nb_nans = 0;
        p->nb_infs = 0;
        p->nb_denormals = 0;
    }
}