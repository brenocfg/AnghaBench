#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int jack_xrun; int /*<<< orphan*/  timefilter; } ;
typedef  TYPE_1__ JackData ;

/* Variables and functions */
 int /*<<< orphan*/  ff_timefilter_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xrun_callback(void *arg)
{
    JackData *self = arg;
    self->jack_xrun = 1;
    ff_timefilter_reset(self->timefilter);
    return 0;
}