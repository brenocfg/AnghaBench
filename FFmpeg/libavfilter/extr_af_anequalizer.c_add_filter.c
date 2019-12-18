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
struct TYPE_6__ {int /*<<< orphan*/  sample_rate; } ;
struct TYPE_5__ {size_t nb_filters; int nb_allocated; int /*<<< orphan*/ * filters; } ;
typedef  int /*<<< orphan*/  EqualizatorFilter ;
typedef  TYPE_1__ AudioNEqualizerContext ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_calloc (int,int) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  equalizer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int add_filter(AudioNEqualizerContext *s, AVFilterLink *inlink)
{
    equalizer(&s->filters[s->nb_filters], inlink->sample_rate);
    if (s->nb_filters >= s->nb_allocated) {
        EqualizatorFilter *filters;

        filters = av_calloc(s->nb_allocated, 2 * sizeof(*s->filters));
        if (!filters)
            return AVERROR(ENOMEM);
        memcpy(filters, s->filters, sizeof(*s->filters) * s->nb_allocated);
        av_free(s->filters);
        s->filters = filters;
        s->nb_allocated *= 2;
    }
    s->nb_filters++;

    return 0;
}