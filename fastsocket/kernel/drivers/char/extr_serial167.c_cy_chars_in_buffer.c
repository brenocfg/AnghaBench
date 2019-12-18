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
struct cyclades_port {int xmit_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cy_chars_in_buffer(struct tty_struct *tty)
{
	struct cyclades_port *info = tty->driver_data;

#ifdef SERIAL_DEBUG_IO
	printk("cy_chars_in_buffer %s %d\n", tty->name, info->xmit_cnt);	/* */
#endif

	if (serial_paranoia_check(info, tty->name, "cy_chars_in_buffer"))
		return 0;

	return info->xmit_cnt;
}