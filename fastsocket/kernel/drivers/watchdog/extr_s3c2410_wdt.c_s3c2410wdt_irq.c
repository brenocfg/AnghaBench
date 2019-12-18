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
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  s3c2410wdt_keepalive () ; 
 int /*<<< orphan*/  wdt_dev ; 

__attribute__((used)) static irqreturn_t s3c2410wdt_irq(int irqno, void *param)
{
	dev_info(wdt_dev, "watchdog timer expired (irq)\n");

	s3c2410wdt_keepalive();
	return IRQ_HANDLED;
}