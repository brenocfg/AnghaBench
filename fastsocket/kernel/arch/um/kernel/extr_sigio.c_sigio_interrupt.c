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
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SIGIO_WRITE_IRQ ; 
 int /*<<< orphan*/  os_read_file (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reactivate_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigio_irq_fd ; 

__attribute__((used)) static irqreturn_t sigio_interrupt(int irq, void *data)
{
	char c;

	os_read_file(sigio_irq_fd, &c, sizeof(c));
	reactivate_fd(sigio_irq_fd, SIGIO_WRITE_IRQ);
	return IRQ_HANDLED;
}