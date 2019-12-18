#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MTU_ICR ; 
 scalar_t__ mtu_base ; 
 TYPE_1__ nmdk_clkevt ; 
 int /*<<< orphan*/  nmdk_count ; 
 scalar_t__ nmdk_cycle ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t nmdk_timer_interrupt(int irq, void *dev_id)
{
	/* ack: "interrupt clear register" */
	writel( 1 << 0, mtu_base + MTU_ICR);

	/* we can't count lost ticks, unfortunately */
	nmdk_count += nmdk_cycle;
	nmdk_clkevt.event_handler(&nmdk_clkevt);

	return IRQ_HANDLED;
}