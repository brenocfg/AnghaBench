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
struct cnic_local {int /*<<< orphan*/  (* ack_int ) (struct cnic_dev*) ;} ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cnic_doirq (struct cnic_dev*) ; 
 int /*<<< orphan*/  stub1 (struct cnic_dev*) ; 

__attribute__((used)) static irqreturn_t cnic_irq(int irq, void *dev_instance)
{
	struct cnic_dev *dev = dev_instance;
	struct cnic_local *cp = dev->cnic_priv;

	if (cp->ack_int)
		cp->ack_int(dev);

	cnic_doirq(dev);

	return IRQ_HANDLED;
}