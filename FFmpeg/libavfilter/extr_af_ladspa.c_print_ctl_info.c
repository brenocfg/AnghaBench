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
struct TYPE_7__ {TYPE_1__* desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  HintDescriptor; scalar_t__ UpperBound; scalar_t__ LowerBound; } ;
struct TYPE_5__ {int /*<<< orphan*/ * PortNames; TYPE_2__* PortRangeHints; } ;
typedef  TYPE_2__ LADSPA_PortRangeHint ;
typedef  scalar_t__ LADSPA_Data ;
typedef  TYPE_3__ LADSPAContext ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 scalar_t__ LADSPA_IS_HINT_BOUNDED_ABOVE (int /*<<< orphan*/ ) ; 
 scalar_t__ LADSPA_IS_HINT_BOUNDED_BELOW (int /*<<< orphan*/ ) ; 
 scalar_t__ LADSPA_IS_HINT_HAS_DEFAULT (int /*<<< orphan*/ ) ; 
 scalar_t__ LADSPA_IS_HINT_INTEGER (int /*<<< orphan*/ ) ; 
 scalar_t__ LADSPA_IS_HINT_LOGARITHMIC (int /*<<< orphan*/ ) ; 
 scalar_t__ LADSPA_IS_HINT_SAMPLE_RATE (int /*<<< orphan*/ ) ; 
 scalar_t__ LADSPA_IS_HINT_TOGGLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int,char*,...) ; 

__attribute__((used)) static void print_ctl_info(AVFilterContext *ctx, int level,
                           LADSPAContext *s, int ctl, unsigned long *map,
                           LADSPA_Data *values, int print)
{
    const LADSPA_PortRangeHint *h = s->desc->PortRangeHints + map[ctl];

    av_log(ctx, level, "c%i: %s [", ctl, s->desc->PortNames[map[ctl]]);

    if (LADSPA_IS_HINT_TOGGLED(h->HintDescriptor)) {
        av_log(ctx, level, "toggled (1 or 0)");

        if (LADSPA_IS_HINT_HAS_DEFAULT(h->HintDescriptor))
            av_log(ctx, level, " (default %i)", (int)values[ctl]);
    } else {
        if (LADSPA_IS_HINT_INTEGER(h->HintDescriptor)) {
            av_log(ctx, level, "<int>");

            if (LADSPA_IS_HINT_BOUNDED_BELOW(h->HintDescriptor))
                av_log(ctx, level, ", min: %i", (int)h->LowerBound);

            if (LADSPA_IS_HINT_BOUNDED_ABOVE(h->HintDescriptor))
                av_log(ctx, level, ", max: %i", (int)h->UpperBound);

            if (print)
                av_log(ctx, level, " (value %d)", (int)values[ctl]);
            else if (LADSPA_IS_HINT_HAS_DEFAULT(h->HintDescriptor))
                av_log(ctx, level, " (default %d)", (int)values[ctl]);
        } else {
            av_log(ctx, level, "<float>");

            if (LADSPA_IS_HINT_BOUNDED_BELOW(h->HintDescriptor))
                av_log(ctx, level, ", min: %f", h->LowerBound);

            if (LADSPA_IS_HINT_BOUNDED_ABOVE(h->HintDescriptor))
                av_log(ctx, level, ", max: %f", h->UpperBound);

            if (print)
                av_log(ctx, level, " (value %f)", values[ctl]);
            else if (LADSPA_IS_HINT_HAS_DEFAULT(h->HintDescriptor))
                av_log(ctx, level, " (default %f)", values[ctl]);
        }

        if (LADSPA_IS_HINT_SAMPLE_RATE(h->HintDescriptor))
            av_log(ctx, level, ", multiple of sample rate");

        if (LADSPA_IS_HINT_LOGARITHMIC(h->HintDescriptor))
            av_log(ctx, level, ", logarithmic scale");
    }

    av_log(ctx, level, "]\n");
}