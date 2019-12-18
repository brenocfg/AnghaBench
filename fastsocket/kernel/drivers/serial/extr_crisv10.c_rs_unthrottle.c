#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ count; } ;
struct TYPE_4__ {scalar_t__ (* chars_in_buffer ) (struct tty_struct*) ;} ;
struct tty_struct {TYPE_3__* termios; TYPE_2__ flip; TYPE_1__ ldisc; scalar_t__ driver_data; } ;
struct e100_serial {scalar_t__ x_char; int /*<<< orphan*/  line; } ;
struct TYPE_6__ {int c_cflag; } ;

/* Variables and functions */
 int CRTSCTS ; 
 int /*<<< orphan*/  DEBUG_LOG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  START_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  e100_rts (struct e100_serial*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rs_send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct tty_struct*) ; 
 scalar_t__ stub2 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_name (struct tty_struct*,char*) ; 

__attribute__((used)) static void
rs_unthrottle(struct tty_struct * tty)
{
	struct e100_serial *info = (struct e100_serial *)tty->driver_data;
#ifdef SERIAL_DEBUG_THROTTLE
	char	buf[64];

	printk("unthrottle %s: %lu....\n", tty_name(tty, buf),
	       (unsigned long)tty->ldisc.chars_in_buffer(tty));
#endif
	DFLOW(DEBUG_LOG(info->line,"rs_unthrottle ldisc %d\n", tty->ldisc.chars_in_buffer(tty)));
	DFLOW(DEBUG_LOG(info->line,"rs_unthrottle flip.count: %i\n", tty->flip.count));
	/* Do RTS before XOFF since XOFF might take some time */
	if (tty->termios->c_cflag & CRTSCTS) {
		/* Assert RTS line  */
		e100_rts(info, 1);
	}

	if (I_IXOFF(tty)) {
		if (info->x_char)
			info->x_char = 0;
		else
			rs_send_xchar(tty, START_CHAR(tty));
	}

}