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
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; TYPE_1__* tx_cur; } ;
typedef  TYPE_2__ ser_info_t ;
struct TYPE_4__ {int status; } ;

/* Variables and functions */
 int BD_SC_READY ; 
 int TX_BUF_SIZE ; 
 int /*<<< orphan*/  TX_WAKEUP ; 
 scalar_t__ serial_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rs_360_write_room(struct tty_struct *tty)
{
	ser_info_t *info = (ser_info_t *)tty->driver_data;
	int	ret;

	if (serial_paranoia_check(info, tty->name, "rs_write_room"))
		return 0;

	if ((info->tx_cur->status & BD_SC_READY) == 0) {
		info->flags &= ~TX_WAKEUP;
		ret = TX_BUF_SIZE;
	}
	else {
		info->flags |= TX_WAKEUP;
		ret = 0;
	}
	return ret;
}