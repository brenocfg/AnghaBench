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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMFA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ ITUBASE ; 
 scalar_t__ TSR ; 
 int /*<<< orphan*/  ctrl_bclr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  h8300_timer_tick () ; 

__attribute__((used)) static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	h8300_timer_tick();
	ctrl_bclr(IMFA, ITUBASE + TSR);
	return IRQ_HANDLED;
}