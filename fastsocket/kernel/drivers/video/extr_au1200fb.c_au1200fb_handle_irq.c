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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  intstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  au_sync () ; 
 TYPE_1__* lcd ; 

__attribute__((used)) static irqreturn_t au1200fb_handle_irq(int irq, void* dev_id)
{
	/* Nothing to do for now, just clear any pending interrupt */
	lcd->intstatus = lcd->intstatus;
	au_sync();

	return IRQ_HANDLED;
}