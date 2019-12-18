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
typedef  int u32 ;
struct whcrc {int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  event_work; scalar_t__ rc_base; TYPE_1__* umc_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ URCSTS ; 
 int URCSTS_ER ; 
 int URCSTS_HSE ; 
 int URCSTS_INT_MASK ; 
 int URCSTS_RCI ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int le_readl (scalar_t__) ; 
 int /*<<< orphan*/  le_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
irqreturn_t whcrc_irq_cb(int irq, void *_whcrc)
{
	struct whcrc *whcrc = _whcrc;
	struct device *dev = &whcrc->umc_dev->dev;
	u32 urcsts;

	urcsts = le_readl(whcrc->rc_base + URCSTS);
	if (!(urcsts & URCSTS_INT_MASK))
		return IRQ_NONE;
	le_writel(urcsts & URCSTS_INT_MASK, whcrc->rc_base + URCSTS);

	if (urcsts & URCSTS_HSE) {
		dev_err(dev, "host system error -- hardware halted\n");
		/* FIXME: do something sensible here */
		goto out;
	}
	if (urcsts & URCSTS_ER)
		schedule_work(&whcrc->event_work);
	if (urcsts & URCSTS_RCI)
		wake_up_all(&whcrc->cmd_wq);
out:
	return IRQ_HANDLED;
}