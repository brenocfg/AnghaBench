#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int nb_gain_entry; TYPE_1__* gain_entry_tbl; } ;
struct TYPE_7__ {double freq; double gain; } ;
typedef  TYPE_1__ GainEntry ;
typedef  TYPE_2__ FIREqualizerContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (TYPE_1__*) ; 
 TYPE_1__* bsearch (double*,TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  gain_entry_compare ; 

__attribute__((used)) static double cubic_interpolate_func(void *p, double freq)
{
    AVFilterContext *ctx = p;
    FIREqualizerContext *s = ctx->priv;
    GainEntry *res;
    double x, x2, x3;
    double a, b, c, d;
    double m0, m1, m2, msum, unit;

    if (!s->nb_gain_entry)
        return 0;

    if (freq <= s->gain_entry_tbl[0].freq)
        return s->gain_entry_tbl[0].gain;

    if (freq >= s->gain_entry_tbl[s->nb_gain_entry-1].freq)
        return s->gain_entry_tbl[s->nb_gain_entry-1].gain;

    res = bsearch(&freq, &s->gain_entry_tbl, s->nb_gain_entry - 1, sizeof(*res), gain_entry_compare);
    av_assert0(res);

    unit = res[1].freq - res[0].freq;
    m0 = res != s->gain_entry_tbl ?
         unit * (res[0].gain - res[-1].gain) / (res[0].freq - res[-1].freq) : 0;
    m1 = res[1].gain - res[0].gain;
    m2 = res != s->gain_entry_tbl + s->nb_gain_entry - 2 ?
         unit * (res[2].gain - res[1].gain) / (res[2].freq - res[1].freq) : 0;

    msum = fabs(m0) + fabs(m1);
    m0 = msum > 0 ? (fabs(m0) * m1 + fabs(m1) * m0) / msum : 0;
    msum = fabs(m1) + fabs(m2);
    m1 = msum > 0 ? (fabs(m1) * m2 + fabs(m2) * m1) / msum : 0;

    d = res[0].gain;
    c = m0;
    b = 3 * res[1].gain - m1 - 2 * c - 3 * d;
    a = res[1].gain - b - c - d;

    x = (freq - res[0].freq) / unit;
    x2 = x * x;
    x3 = x2 * x;

    return a * x3 + b * x2 + c * x + d;
}