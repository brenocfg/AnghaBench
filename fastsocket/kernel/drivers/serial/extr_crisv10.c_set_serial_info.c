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
struct serial_struct {scalar_t__ type; scalar_t__ close_delay; int flags; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  baud_base; } ;
struct TYPE_4__ {TYPE_1__* tty; } ;
struct e100_serial {scalar_t__ type; scalar_t__ close_delay; int flags; int count; TYPE_2__ port; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  baud_base; } ;
typedef  int /*<<< orphan*/  new_serial ;
struct TYPE_3__ {int low_latency; } ;

/* Variables and functions */
 int ASYNC_FLAGS ; 
 int ASYNC_INITIALIZED ; 
 int ASYNC_LOW_LATENCY ; 
 int ASYNC_USR_MASK ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EBUSY ; 
 int EFAULT ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_speed (struct e100_serial*) ; 
 scalar_t__ copy_from_user (struct serial_struct*,struct serial_struct*,int) ; 
 int startup (struct e100_serial*) ; 

__attribute__((used)) static int
set_serial_info(struct e100_serial *info,
		struct serial_struct *new_info)
{
	struct serial_struct new_serial;
	struct e100_serial old_info;
	int retval = 0;

	if (copy_from_user(&new_serial, new_info, sizeof(new_serial)))
		return -EFAULT;

	old_info = *info;

	if (!capable(CAP_SYS_ADMIN)) {
		if ((new_serial.type != info->type) ||
		    (new_serial.close_delay != info->close_delay) ||
		    ((new_serial.flags & ~ASYNC_USR_MASK) !=
		     (info->flags & ~ASYNC_USR_MASK)))
			return -EPERM;
		info->flags = ((info->flags & ~ASYNC_USR_MASK) |
			       (new_serial.flags & ASYNC_USR_MASK));
		goto check_and_exit;
	}

	if (info->count > 1)
		return -EBUSY;

	/*
	 * OK, past this point, all the error checking has been done.
	 * At this point, we start making changes.....
	 */

	info->baud_base = new_serial.baud_base;
	info->flags = ((info->flags & ~ASYNC_FLAGS) |
		       (new_serial.flags & ASYNC_FLAGS));
	info->custom_divisor = new_serial.custom_divisor;
	info->type = new_serial.type;
	info->close_delay = new_serial.close_delay;
	info->closing_wait = new_serial.closing_wait;
	info->port.tty->low_latency = (info->flags & ASYNC_LOW_LATENCY) ? 1 : 0;

 check_and_exit:
	if (info->flags & ASYNC_INITIALIZED) {
		change_speed(info);
	} else
		retval = startup(info);
	return retval;
}