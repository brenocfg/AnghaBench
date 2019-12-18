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
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  process_intrq (struct adapter*) ; 
 int /*<<< orphan*/  t4_slow_intr_handler (struct adapter*) ; 

__attribute__((used)) static irqreturn_t t4_intr_msi(int irq, void *cookie)
{
	struct adapter *adap = cookie;

	t4_slow_intr_handler(adap);
	process_intrq(adap);
	return IRQ_HANDLED;
}