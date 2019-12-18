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
struct lapb_cb {int condition; } ;

/* Variables and functions */
 int LAPB_ACK_PENDING_CONDITION ; 
 int /*<<< orphan*/  lapb_timeout_response (struct lapb_cb*) ; 

__attribute__((used)) static void lapb_t2timer_expiry(unsigned long param)
{
	struct lapb_cb *lapb = (struct lapb_cb *)param;

	if (lapb->condition & LAPB_ACK_PENDING_CONDITION) {
		lapb->condition &= ~LAPB_ACK_PENDING_CONDITION;
		lapb_timeout_response(lapb);
	}
}