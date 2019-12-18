#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int depth; int table_size; int freq; double* table; scalar_t__ index; } ;
typedef  TYPE_1__ TremoloContext ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int sample_rate; TYPE_3__* dst; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int M_PI ; 
 double* av_malloc_array (int,int) ; 
 int fabs (double const) ; 
 int fmod (double,double) ; 
 double sin (int) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    TremoloContext *s = ctx->priv;
    const double offset = 1. - s->depth / 2.;
    int i;

    s->table_size = inlink->sample_rate / s->freq;
    s->table = av_malloc_array(s->table_size, sizeof(*s->table));
    if (!s->table)
        return AVERROR(ENOMEM);

    for (i = 0; i < s->table_size; i++) {
        double env = s->freq * i / inlink->sample_rate;
        env = sin(2 * M_PI * fmod(env + 0.25, 1.0));
        s->table[i] = env * (1 - fabs(offset)) + offset;
    }

    s->index = 0;

    return 0;
}