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
struct loopback_pcm {unsigned int pcm_rate_shift; scalar_t__ period_size_frac; scalar_t__ irq_pos; int period_update_pending; unsigned long pcm_bps; TYPE_1__ timer; int /*<<< orphan*/  pcm_period_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ frac_pos (struct loopback_pcm*,int /*<<< orphan*/ ) ; 
 unsigned int get_rate_shift (struct loopback_pcm*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void loopback_timer_start(struct loopback_pcm *dpcm)
{
	unsigned long tick;
	unsigned int rate_shift = get_rate_shift(dpcm);

	if (rate_shift != dpcm->pcm_rate_shift) {
		dpcm->pcm_rate_shift = rate_shift;
		dpcm->period_size_frac = frac_pos(dpcm, dpcm->pcm_period_size);
	}
	if (dpcm->period_size_frac <= dpcm->irq_pos) {
		dpcm->irq_pos %= dpcm->period_size_frac;
		dpcm->period_update_pending = 1;
	}
	tick = dpcm->period_size_frac - dpcm->irq_pos;
	tick = (tick + dpcm->pcm_bps - 1) / dpcm->pcm_bps;
	dpcm->timer.expires = jiffies + tick;
	add_timer(&dpcm->timer);
}