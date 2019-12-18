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
struct async_struct {int /*<<< orphan*/  last_active; int /*<<< orphan*/  tty; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct async_struct* IRQ_ports ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  receive_chars (struct async_struct*) ; 

__attribute__((used)) static irqreturn_t ser_rx_int(int irq, void *dev_id)
{
	struct async_struct * info;

#ifdef SERIAL_DEBUG_INTR
	printk("ser_rx_int...");
#endif

	info = IRQ_ports;
	if (!info || !info->tty)
		return IRQ_NONE;

	receive_chars(info);
	info->last_active = jiffies;
#ifdef SERIAL_DEBUG_INTR
	printk("end.\n");
#endif
	return IRQ_HANDLED;
}