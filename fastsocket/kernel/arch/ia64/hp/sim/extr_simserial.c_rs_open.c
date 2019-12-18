#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; int low_latency; int /*<<< orphan*/  name; struct async_struct* driver_data; } ;
struct file {int dummy; } ;
struct async_struct {int flags; int /*<<< orphan*/  line; int /*<<< orphan*/  close_wait; struct tty_struct* tty; TYPE_1__* state; } ;
struct TYPE_5__ {int flags; struct TYPE_5__* next; scalar_t__ write; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int ASYNC_CLOSING ; 
 int ASYNC_HUP_NOTIFY ; 
 int ASYNC_LOW_LATENCY ; 
 int CON_ENABLED ; 
 int EAGAIN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NR_PORTS ; 
 TYPE_2__* console ; 
 TYPE_2__* console_drivers ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int get_async_struct (int,struct async_struct**) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int startup (struct async_struct*) ; 
 unsigned char* tmp_buf ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 

__attribute__((used)) static int rs_open(struct tty_struct *tty, struct file * filp)
{
	struct async_struct	*info;
	int			retval, line;
	unsigned long		page;

	line = tty->index;
	if ((line < 0) || (line >= NR_PORTS))
		return -ENODEV;
	retval = get_async_struct(line, &info);
	if (retval)
		return retval;
	tty->driver_data = info;
	info->tty = tty;

#ifdef SIMSERIAL_DEBUG
	printk("rs_open %s, count = %d\n", tty->name, info->state->count);
#endif
	info->tty->low_latency = (info->flags & ASYNC_LOW_LATENCY) ? 1 : 0;

	if (!tmp_buf) {
		page = get_zeroed_page(GFP_KERNEL);
		if (!page)
			return -ENOMEM;
		if (tmp_buf)
			free_page(page);
		else
			tmp_buf = (unsigned char *) page;
	}

	/*
	 * If the port is the middle of closing, bail out now
	 */
	if (tty_hung_up_p(filp) ||
	    (info->flags & ASYNC_CLOSING)) {
		if (info->flags & ASYNC_CLOSING)
			interruptible_sleep_on(&info->close_wait);
#ifdef SERIAL_DO_RESTART
		return ((info->flags & ASYNC_HUP_NOTIFY) ?
			-EAGAIN : -ERESTARTSYS);
#else
		return -EAGAIN;
#endif
	}

	/*
	 * Start up serial port
	 */
	retval = startup(info);
	if (retval) {
		return retval;
	}

	/*
	 * figure out which console to use (should be one already)
	 */
	console = console_drivers;
	while (console) {
		if ((console->flags & CON_ENABLED) && console->write) break;
		console = console->next;
	}

#ifdef SIMSERIAL_DEBUG
	printk("rs_open ttys%d successful\n", info->line);
#endif
	return 0;
}