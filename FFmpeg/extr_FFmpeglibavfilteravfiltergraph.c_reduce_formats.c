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
struct TYPE_3__ {int nb_filters; int /*<<< orphan*/ * filters; } ;
typedef  TYPE_1__ AVFilterGraph ;

/* Variables and functions */
 int reduce_formats_on_filter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reduce_formats(AVFilterGraph *graph)
{
    int i, reduced, ret;

    do {
        reduced = 0;

        for (i = 0; i < graph->nb_filters; i++) {
            if ((ret = reduce_formats_on_filter(graph->filters[i])) < 0)
                return ret;
            reduced |= ret;
        }
    } while (reduced);

    return 0;
}