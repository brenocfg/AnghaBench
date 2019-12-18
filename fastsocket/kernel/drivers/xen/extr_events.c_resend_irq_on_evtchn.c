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
struct shared_info {int /*<<< orphan*/  evtchn_pending; int /*<<< orphan*/  evtchn_mask; } ;

/* Variables and functions */
 struct shared_info* HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  VALID_EVTCHN (int) ; 
 int evtchn_from_irq (unsigned int) ; 
 int /*<<< orphan*/  sync_set_bit (int,int /*<<< orphan*/ ) ; 
 int sync_test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmask_evtchn (int) ; 

int resend_irq_on_evtchn(unsigned int irq)
{
	int masked, evtchn = evtchn_from_irq(irq);
	struct shared_info *s = HYPERVISOR_shared_info;

	if (!VALID_EVTCHN(evtchn))
		return 1;

	masked = sync_test_and_set_bit(evtchn, s->evtchn_mask);
	sync_set_bit(evtchn, s->evtchn_pending);
	if (!masked)
		unmask_evtchn(evtchn);

	return 1;
}