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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  gfar_schedule_cleanup (struct net_device*) ; 

__attribute__((used)) static irqreturn_t gfar_transmit(int irq, void *dev_id)
{
	gfar_schedule_cleanup((struct net_device *)dev_id);
	return IRQ_HANDLED;
}