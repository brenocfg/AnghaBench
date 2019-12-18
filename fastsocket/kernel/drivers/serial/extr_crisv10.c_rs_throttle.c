#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ (* chars_in_buffer ) (struct tty_struct*) ;} ;
struct tty_struct {TYPE_1__* termios; TYPE_2__ ldisc; scalar_t__ driver_data; } ;
struct e100_serial {int /*<<< orphan*/  line; } ;
struct TYPE_3__ {int c_cflag; } ;

/* Variables and functions */
 int CRTSCTS ; 
 int /*<<< orphan*/  DEBUG_LOG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  e100_rts (struct e100_serial*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rs_send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct tty_struct*) ; 
 scalar_t__ stub2 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_name (struct tty_struct*,char*) ; 

__attribute__((used)) static void
rs_throttle(struct tty_struct * tty)
{
	struct e100_serial *info = (struct e100_serial *)tty->driver_data;
#ifdef SERIAL_DEBUG_THROTTLE
	char	buf[64];

	printk("throttle %s: %lu....\n", tty_name(tty, buf),
	       (unsigned long)tty->ldisc.chars_in_buffer(tty));
#endif
	DFLOW(DEBUG_LOG(info->line,"rs_throttle %lu\n", tty->ldisc.chars_in_buffer(tty)));

	/* Do RTS before XOFF since XOFF might take some time */
	if (tty->termios->c_cflag & CRTSCTS) {
		/* Turn off RTS line */
		e100_rts(info, 0);
	}
	if (I_IXOFF(tty))
		rs_send_xchar(tty, STOP_CHAR(tty));

}