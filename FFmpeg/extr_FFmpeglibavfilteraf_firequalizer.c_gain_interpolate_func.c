#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {double freq; double gain; } ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int nb_gain_entry; TYPE_5__* gain_entry_tbl; } ;
struct TYPE_7__ {double freq; double gain; } ;
typedef  TYPE_1__ GainEntry ;
typedef  TYPE_2__ FIREqualizerContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (TYPE_1__*) ; 
 TYPE_1__* bsearch (double*,TYPE_5__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gain_entry_compare ; 
 scalar_t__ isnan (double) ; 

__attribute__((used)) static double gain_interpolate_func(void *p, double freq)
{
    AVFilterContext *ctx = p;
    FIREqualizerContext *s = ctx->priv;
    GainEntry *res;
    double d0, d1, d;

    if (isnan(freq))
        return freq;

    if (!s->nb_gain_entry)
        return 0;

    if (freq <= s->gain_entry_tbl[0].freq)
        return s->gain_entry_tbl[0].gain;

    if (freq >= s->gain_entry_tbl[s->nb_gain_entry-1].freq)
        return s->gain_entry_tbl[s->nb_gain_entry-1].gain;

    res = bsearch(&freq, &s->gain_entry_tbl, s->nb_gain_entry - 1, sizeof(*res), gain_entry_compare);
    av_assert0(res);

    d  = res[1].freq - res[0].freq;
    d0 = freq - res[0].freq;
    d1 = res[1].freq - freq;

    if (d0 && d1)
        return (d0 * res[1].gain + d1 * res[0].gain) / d;

    if (d0)
        return res[1].gain;

    return res[0].gain;
}