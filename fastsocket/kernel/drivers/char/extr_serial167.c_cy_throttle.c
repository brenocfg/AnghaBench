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
typedef  unsigned char u_char ;
struct TYPE_2__ {int /*<<< orphan*/  (* chars_in_buffer ) (struct tty_struct*) ;} ;
struct tty_struct {int /*<<< orphan*/  name; TYPE_1__ ldisc; struct cyclades_port* driver_data; } ;
struct cyclades_port {int line; int /*<<< orphan*/  x_char; } ;

/* Variables and functions */
 scalar_t__ BASE_ADDR ; 
 size_t CyCAR ; 
 size_t CyMSVR1 ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_name (struct tty_struct*,char*) ; 

__attribute__((used)) static void cy_throttle(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;
	unsigned long flags;
	volatile unsigned char *base_addr = (u_char *) BASE_ADDR;
	int channel;

#ifdef SERIAL_DEBUG_THROTTLE
	char buf[64];

	printk("throttle %s: %d....\n", tty_name(tty, buf),
	       tty->ldisc.chars_in_buffer(tty));
	printk("cy_throttle %s\n", tty->name);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_nthrottle")) {
		return;
	}

	if (I_IXOFF(tty)) {
		info->x_char = STOP_CHAR(tty);
		/* Should use the "Send Special Character" feature!!! */
	}

	channel = info->line;

	local_irq_save(flags);
	base_addr[CyCAR] = (u_char) channel;
	base_addr[CyMSVR1] = 0;
	local_irq_restore(flags);
}