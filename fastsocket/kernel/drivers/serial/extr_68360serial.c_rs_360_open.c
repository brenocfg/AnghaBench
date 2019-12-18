#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int index; int name; TYPE_3__* driver_data; } ;
struct file {int dummy; } ;
struct TYPE_9__ {struct tty_struct* tty; } ;
struct TYPE_10__ {TYPE_2__ port; TYPE_1__* state; } ;
typedef  TYPE_3__ ser_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int ENODEV ; 
 int NR_PORTS ; 
 int block_til_ready (struct tty_struct*,struct file*,TYPE_3__*) ; 
 int get_async_struct (int,TYPE_3__**) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 scalar_t__ serial_paranoia_check (TYPE_3__*,int,char*) ; 
 int startup (TYPE_3__*) ; 

__attribute__((used)) static int rs_360_open(struct tty_struct *tty, struct file * filp)
{
	ser_info_t	*info;
	int 		retval, line;

	line = tty->index;
	if ((line < 0) || (line >= NR_PORTS))
		return -ENODEV;
	retval = get_async_struct(line, &info);
	if (retval)
		return retval;
	if (serial_paranoia_check(info, tty->name, "rs_open"))
		return -ENODEV;

#ifdef SERIAL_DEBUG_OPEN
	printk("rs_open %s, count = %d\n", tty->name, info->state->count);
#endif
	tty->driver_data = info;
	info->port.tty = tty;

	/*
	 * Start up serial port
	 */
	retval = startup(info);
	if (retval)
		return retval;

	retval = block_til_ready(tty, filp, info);
	if (retval) {
#ifdef SERIAL_DEBUG_OPEN
		printk("rs_open returning after block_til_ready with %d\n",
		       retval);
#endif
		return retval;
	}

#ifdef SERIAL_DEBUG_OPEN
	printk("rs_open %s successful...", tty->name);
#endif
	return 0;
}