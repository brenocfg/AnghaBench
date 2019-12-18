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
struct locomokbd {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  locomokbd_scankeyboard (struct locomokbd*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static irqreturn_t locomokbd_interrupt(int irq, void *dev_id)
{
	struct locomokbd *locomokbd = dev_id;
	/** wait chattering delay **/
	udelay(100);

	locomokbd_scankeyboard(locomokbd);

	return IRQ_HANDLED;
}