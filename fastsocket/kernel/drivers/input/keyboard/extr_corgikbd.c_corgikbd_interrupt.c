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
struct corgikbd {int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  corgikbd_scankeyboard (struct corgikbd*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static irqreturn_t corgikbd_interrupt(int irq, void *dev_id)
{
	struct corgikbd *corgikbd_data = dev_id;

	if (!timer_pending(&corgikbd_data->timer)) {
		/** wait chattering delay **/
		udelay(20);
		corgikbd_scankeyboard(corgikbd_data);
	}

	return IRQ_HANDLED;
}