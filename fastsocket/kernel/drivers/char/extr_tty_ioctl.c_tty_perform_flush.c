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
struct tty_struct {int dummy; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_buffer ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  TCIFLUSH 130 
#define  TCIOFLUSH 129 
#define  TCOFLUSH 128 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*) ; 
 int tty_check_change (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_ref_wait (struct tty_struct*) ; 

int tty_perform_flush(struct tty_struct *tty, unsigned long arg)
{
	struct tty_ldisc *ld;
	int retval = tty_check_change(tty);
	if (retval)
		return retval;

	ld = tty_ldisc_ref_wait(tty);
	switch (arg) {
	case TCIFLUSH:
		if (ld && ld->ops->flush_buffer)
			ld->ops->flush_buffer(tty);
		break;
	case TCIOFLUSH:
		if (ld && ld->ops->flush_buffer)
			ld->ops->flush_buffer(tty);
		/* fall through */
	case TCOFLUSH:
		tty_driver_flush_buffer(tty);
		break;
	default:
		tty_ldisc_deref(ld);
		return -EINVAL;
	}
	tty_ldisc_deref(ld);
	return 0;
}