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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ sn_in_service_ivecs; } ;

/* Variables and functions */
 int HUB_L (int*) ; 
 int /*<<< orphan*/  HUB_S (int*,int) ; 
 scalar_t__ LOCAL_MMR_ADDR (int /*<<< orphan*/ ) ; 
 int SH_ALL_INT_MASK ; 
 int /*<<< orphan*/  SH_EVENT_OCCURRED ; 
 int /*<<< orphan*/  SH_EVENT_OCCURRED_ALIAS ; 
 int /*<<< orphan*/  __set_bit (unsigned int,void volatile*) ; 
 int /*<<< orphan*/  move_native_irq (unsigned int) ; 
 TYPE_1__* pda ; 

__attribute__((used)) static void sn_ack_irq(unsigned int irq)
{
	u64 event_occurred, mask;

	irq = irq & 0xff;
	event_occurred = HUB_L((u64*)LOCAL_MMR_ADDR(SH_EVENT_OCCURRED));
	mask = event_occurred & SH_ALL_INT_MASK;
	HUB_S((u64*)LOCAL_MMR_ADDR(SH_EVENT_OCCURRED_ALIAS), mask);
	__set_bit(irq, (volatile void *)pda->sn_in_service_ivecs);

	move_native_irq(irq);
}