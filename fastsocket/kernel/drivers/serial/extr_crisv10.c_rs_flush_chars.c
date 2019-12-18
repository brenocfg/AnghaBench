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
struct tty_struct {scalar_t__ hw_stopped; scalar_t__ stopped; scalar_t__ driver_data; } ;
struct TYPE_2__ {scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  buf; } ;
struct e100_serial {TYPE_1__ xmit; scalar_t__ tr_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  start_transmit (struct e100_serial*) ; 

__attribute__((used)) static void
rs_flush_chars(struct tty_struct *tty)
{
	struct e100_serial *info = (struct e100_serial *)tty->driver_data;
	unsigned long flags;

	if (info->tr_running ||
	    info->xmit.head == info->xmit.tail ||
	    tty->stopped ||
	    tty->hw_stopped ||
	    !info->xmit.buf)
		return;

#ifdef SERIAL_DEBUG_FLOW
	printk("rs_flush_chars\n");
#endif

	/* this protection might not exactly be necessary here */

	local_irq_save(flags);
	start_transmit(info);
	local_irq_restore(flags);
}