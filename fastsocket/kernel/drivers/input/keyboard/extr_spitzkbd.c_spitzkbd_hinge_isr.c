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
struct spitzkbd {int /*<<< orphan*/  htimer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HINGE_SCAN_INTERVAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t spitzkbd_hinge_isr(int irq, void *dev_id)
{
	struct spitzkbd *spitzkbd_data = dev_id;

	if (!timer_pending(&spitzkbd_data->htimer))
		mod_timer(&spitzkbd_data->htimer, jiffies + msecs_to_jiffies(HINGE_SCAN_INTERVAL));

	return IRQ_HANDLED;
}