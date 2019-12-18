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
struct mg_host {void (* mg_do_intr ) (struct mg_host*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 void mg_unexpected_intr (struct mg_host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mg_irq(int irq, void *dev_id)
{
	struct mg_host *host = dev_id;
	void (*handler)(struct mg_host *) = host->mg_do_intr;

	spin_lock(&host->lock);

	host->mg_do_intr = NULL;
	del_timer(&host->timer);
	if (!handler)
		handler = mg_unexpected_intr;
	handler(host);

	spin_unlock(&host->lock);

	return IRQ_HANDLED;
}