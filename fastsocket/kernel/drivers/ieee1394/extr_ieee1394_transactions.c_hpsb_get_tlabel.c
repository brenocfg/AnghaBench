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
struct hpsb_packet {int dummy; } ;

/* Variables and functions */
 int hpsb_get_tlabel_atomic (struct hpsb_packet*) ; 
 scalar_t__ in_atomic () ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  tlabel_wq ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int hpsb_get_tlabel(struct hpsb_packet *packet)
{
	if (irqs_disabled() || in_atomic())
		return hpsb_get_tlabel_atomic(packet);

	/* NB: The macro wait_event_interruptible() is called with a condition
	 * argument with side effect.  This is only possible because the side
	 * effect does not occur until the condition became true, and
	 * wait_event_interruptible() won't evaluate the condition again after
	 * that. */
	return wait_event_interruptible(tlabel_wq,
					!hpsb_get_tlabel_atomic(packet));
}