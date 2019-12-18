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
struct TYPE_6__ {int metric_length; } ;
struct TYPE_5__ {int flags; scalar_t__ buffer; int* diffs; int /*<<< orphan*/  breaks; struct TYPE_5__* next; } ;
typedef  TYPE_1__ PullupField ;
typedef  TYPE_2__ PullupContext ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_LEFT ; 
 int /*<<< orphan*/  BREAK_RIGHT ; 
 int F_HAVE_BREAKS ; 

__attribute__((used)) static void compute_breaks(PullupContext *s, PullupField *f0)
{
    PullupField *f1 = f0->next;
    PullupField *f2 = f1->next;
    PullupField *f3 = f2->next;
    int i, l, max_l = 0, max_r = 0;

    if (f0->flags & F_HAVE_BREAKS)
        return;

    f0->flags |= F_HAVE_BREAKS;

    /* Special case when fields are 100% identical */
    if (f0->buffer == f2->buffer && f1->buffer != f3->buffer) {
        f2->breaks |= BREAK_RIGHT;
        return;
    }

    if (f0->buffer != f2->buffer && f1->buffer == f3->buffer) {
        f1->breaks |= BREAK_LEFT;
        return;
    }

    for (i = 0; i < s->metric_length; i++) {
        l = f2->diffs[i] - f3->diffs[i];

        if ( l > max_l)
            max_l =  l;
        if (-l > max_r)
            max_r = -l;
    }

    /* Don't get tripped up when differences are mostly quant error */
    if (max_l + max_r < 128)
        return;
    if (max_l > 4 * max_r)
        f1->breaks |= BREAK_LEFT;
    if (max_r > 4 * max_l)
        f2->breaks |= BREAK_RIGHT;
}