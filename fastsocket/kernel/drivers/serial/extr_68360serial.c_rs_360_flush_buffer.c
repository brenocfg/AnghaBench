#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ser_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  TX_WAKEUP ; 
 scalar_t__ serial_paranoia_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void rs_360_flush_buffer(struct tty_struct *tty)
{
	ser_info_t *info = (ser_info_t *)tty->driver_data;
				
	if (serial_paranoia_check(info, tty->name, "rs_flush_buffer"))
		return;

	/* There is nothing to "flush", whatever we gave the CPM
	 * is on its way out.
	 */
	tty_wakeup(tty);
	info->flags &= ~TX_WAKEUP;
}