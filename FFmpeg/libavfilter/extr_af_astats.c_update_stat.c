#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {double mult; scalar_t__ tc_samples; } ;
struct TYPE_5__ {double min; double nmin; int min_run; int min_count; double last; scalar_t__ min_non_zero; double max; double nmax; int max_run; int max_count; int zero_runs; double last_non_zero; double sigma_x; double sigma_x2; double avg_sigma_x2; double diff1_sum_x2; scalar_t__ nb_samples; void* min_sigma_x2; void* max_sigma_x2; int /*<<< orphan*/  imask; int /*<<< orphan*/  mask; int /*<<< orphan*/  diff1_sum; void* max_diff; void* min_diff; scalar_t__ max_runs; scalar_t__ min_runs; } ;
typedef  TYPE_1__ ChannelStats ;
typedef  TYPE_2__ AudioStatsContext ;

/* Variables and functions */
 scalar_t__ FFABS (double) ; 
 void* FFMAX (void*,double) ; 
 void* FFMIN (void*,double) ; 
 scalar_t__ FFSIGN (double) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  isnan (double) ; 

__attribute__((used)) static inline void update_stat(AudioStatsContext *s, ChannelStats *p, double d, double nd, int64_t i)
{
    if (d < p->min) {
        p->min = d;
        p->nmin = nd;
        p->min_run = 1;
        p->min_runs = 0;
        p->min_count = 1;
    } else if (d == p->min) {
        p->min_count++;
        p->min_run = d == p->last ? p->min_run + 1 : 1;
    } else if (p->last == p->min) {
        p->min_runs += p->min_run * p->min_run;
    }

    if (d != 0 && FFABS(d) < p->min_non_zero)
        p->min_non_zero = FFABS(d);

    if (d > p->max) {
        p->max = d;
        p->nmax = nd;
        p->max_run = 1;
        p->max_runs = 0;
        p->max_count = 1;
    } else if (d == p->max) {
        p->max_count++;
        p->max_run = d == p->last ? p->max_run + 1 : 1;
    } else if (p->last == p->max) {
        p->max_runs += p->max_run * p->max_run;
    }

    if (d != 0) {
        p->zero_runs += FFSIGN(d) != FFSIGN(p->last_non_zero);
        p->last_non_zero = d;
    }

    p->sigma_x += nd;
    p->sigma_x2 += nd * nd;
    p->avg_sigma_x2 = p->avg_sigma_x2 * s->mult + (1.0 - s->mult) * nd * nd;
    if (!isnan(p->last)) {
        p->min_diff = FFMIN(p->min_diff, fabs(d - p->last));
        p->max_diff = FFMAX(p->max_diff, fabs(d - p->last));
        p->diff1_sum += fabs(d - p->last);
        p->diff1_sum_x2 += (d - p->last) * (d - p->last);
    }
    p->last = d;
    p->mask |= i;
    p->imask &= i;

    if (p->nb_samples >= s->tc_samples) {
        p->max_sigma_x2 = FFMAX(p->max_sigma_x2, p->avg_sigma_x2);
        p->min_sigma_x2 = FFMIN(p->min_sigma_x2, p->avg_sigma_x2);
    }
    p->nb_samples++;
}