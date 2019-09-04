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
struct TYPE_3__ {int nb_inputs; int nb_outputs; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_1__ AVFilterContext ;

/* Variables and functions */
 size_t ff_inlink_queued_frames (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_have_queued(AVFilterContext *filter)
{
    for (int j = 0; j < filter->nb_inputs; j++) {
        AVFilterLink *l = filter->inputs[j];
        size_t frames = ff_inlink_queued_frames(l);

        if (frames)
            return 1;
    }

    for (int j = 0; j < filter->nb_outputs; j++) {
        AVFilterLink *l = filter->outputs[j];
        size_t frames = ff_inlink_queued_frames(l);

        if (frames)
            return 1;
    }

    return 0;
}