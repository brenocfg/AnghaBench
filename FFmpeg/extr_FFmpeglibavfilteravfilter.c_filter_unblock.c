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
struct TYPE_5__ {unsigned int nb_outputs; TYPE_1__** outputs; } ;
struct TYPE_4__ {scalar_t__ frame_blocked_in; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */

__attribute__((used)) static void filter_unblock(AVFilterContext *filter)
{
    unsigned i;

    for (i = 0; i < filter->nb_outputs; i++)
        filter->outputs[i]->frame_blocked_in = 0;
}