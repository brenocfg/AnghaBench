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
struct tty_struct {int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct cyclades_port {unsigned char* xmit_buf; int xmit_cnt; int xmit_head; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cy_put_char(struct tty_struct *tty, unsigned char ch)
{
	struct cyclades_port *info = tty->driver_data;
	unsigned long flags;

#ifdef SERIAL_DEBUG_IO
	printk("cy_put_char %s(0x%02x)\n", tty->name, ch);
#endif

	if (serial_paranoia_check(info, tty->name, "cy_put_char"))
		return 0;

	if (!info->xmit_buf)
		return 0;

	local_irq_save(flags);
	if (info->xmit_cnt >= PAGE_SIZE - 1) {
		local_irq_restore(flags);
		return 0;
	}

	info->xmit_buf[info->xmit_head++] = ch;
	info->xmit_head &= PAGE_SIZE - 1;
	info->xmit_cnt++;
	local_irq_restore(flags);
	return 1;
}