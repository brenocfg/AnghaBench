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
struct TYPE_3__ {scalar_t__* window; scalar_t__* window_current; scalar_t__* window_end; int /*<<< orphan*/  sum; } ;
typedef  TYPE_1__ SilenceRemoveContext ;

/* Variables and functions */
 scalar_t__ fabs (double) ; 

__attribute__((used)) static void update_peak(SilenceRemoveContext *s, double sample)
{
    s->sum -= *s->window_current;
    *s->window_current = fabs(sample);
    s->sum += *s->window_current;

    s->window_current++;
    if (s->window_current >= s->window_end)
        s->window_current = s->window;
}