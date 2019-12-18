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
typedef  unsigned char u_char ;
struct tty_struct {int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct cyclades_port {int line; } ;

/* Variables and functions */
 scalar_t__ BASE_ADDR ; 
 size_t CyCAR ; 
 size_t CyIER ; 
 unsigned char volatile CyTxMpty ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cy_start(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;
	volatile unsigned char *base_addr = (unsigned char *)BASE_ADDR;
	int channel;
	unsigned long flags;

#ifdef SERIAL_DEBUG_OTHER
	printk("cy_start %s\n", tty->name);	/* */
#endif

	if (serial_paranoia_check(info, tty->name, "cy_start"))
		return;

	channel = info->line;

	local_irq_save(flags);
	base_addr[CyCAR] = (u_char) (channel);
	base_addr[CyIER] |= CyTxMpty;
	local_irq_restore(flags);
}