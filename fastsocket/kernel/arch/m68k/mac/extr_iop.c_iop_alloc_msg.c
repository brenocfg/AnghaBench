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
struct iop_msg {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ IOP_MSGSTATUS_UNUSED ; 
 scalar_t__ IOP_MSGSTATUS_WAITING ; 
 int NUM_IOP_MSGS ; 
 struct iop_msg* iop_msg_pool ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static struct iop_msg *iop_alloc_msg(void)
{
	int i;
	unsigned long flags;

	local_irq_save(flags);

	for (i = 0 ; i < NUM_IOP_MSGS ; i++) {
		if (iop_msg_pool[i].status == IOP_MSGSTATUS_UNUSED) {
			iop_msg_pool[i].status = IOP_MSGSTATUS_WAITING;
			local_irq_restore(flags);
			return &iop_msg_pool[i];
		}
	}

	local_irq_restore(flags);
	return NULL;
}