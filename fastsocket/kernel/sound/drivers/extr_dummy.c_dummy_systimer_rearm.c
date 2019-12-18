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
struct TYPE_2__ {scalar_t__ expires; } ;
struct dummy_systimer_pcm {int frac_period_rest; int rate; TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void dummy_systimer_rearm(struct dummy_systimer_pcm *dpcm)
{
	dpcm->timer.expires = jiffies +
		(dpcm->frac_period_rest + dpcm->rate - 1) / dpcm->rate;
	add_timer(&dpcm->timer);
}