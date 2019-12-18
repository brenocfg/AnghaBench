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
 scalar_t__ VALID_EVTCHN (int) ; 
 int evtchn_from_irq (unsigned int) ; 
 int /*<<< orphan*/  sync_set_bit (int,int /*<<< orphan*/ ) ; 
 int sync_test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmask_evtchn (int) ; 

__attribute__((used)) static int retrigger_dynirq(unsigned int irq)
{
	int evtchn = evtchn_from_irq(irq);
	struct shared_info *sh = HYPERVISOR_shared_info;
	int ret = 0;

	if (VALID_EVTCHN(evtchn)) {
		int masked;

		masked = sync_test_and_set_bit(evtchn, sh->evtchn_mask);
		sync_set_bit(evtchn, sh->evtchn_pending);
		if (!masked)
			unmask_evtchn(evtchn);
		ret = 1;
	}

	return ret;
}