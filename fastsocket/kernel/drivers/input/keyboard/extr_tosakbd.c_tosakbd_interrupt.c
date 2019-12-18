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
struct tosakbd {int /*<<< orphan*/  timer; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct tosakbd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tosakbd_scankeyboard (struct platform_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static irqreturn_t tosakbd_interrupt(int irq, void *__dev)
{
	struct platform_device *dev = __dev;
	struct tosakbd *tosakbd = platform_get_drvdata(dev);

	if (!timer_pending(&tosakbd->timer)) {
		/** wait chattering delay **/
		udelay(20);
		tosakbd_scankeyboard(dev);
	}

	return IRQ_HANDLED;
}