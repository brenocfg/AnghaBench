#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hdspm {int /*<<< orphan*/  lock; int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_LatencyMask ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  hdspm_compute_period_size (struct hdspm*) ; 
 int /*<<< orphan*/  hdspm_encode_latency (int) ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdspm_set_interrupt_interval(struct hdspm * s, unsigned int frames)
{
	int n;

	spin_lock_irq(&s->lock);

	frames >>= 7;
	n = 0;
	while (frames) {
		n++;
		frames >>= 1;
	}
	s->control_register &= ~HDSPM_LatencyMask;
	s->control_register |= hdspm_encode_latency(n);

	hdspm_write(s, HDSPM_controlRegister, s->control_register);

	hdspm_compute_period_size(s);

	spin_unlock_irq(&s->lock);

	return 0;
}