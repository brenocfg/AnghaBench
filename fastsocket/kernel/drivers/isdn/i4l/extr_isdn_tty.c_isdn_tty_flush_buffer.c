#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_4__ {scalar_t__ xmit_count; } ;
typedef  TYPE_1__ modem_info ;

/* Variables and functions */
 int /*<<< orphan*/  isdn_tty_cleanup_xmit (TYPE_1__*) ; 
 scalar_t__ isdn_tty_paranoia_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void
isdn_tty_flush_buffer(struct tty_struct *tty)
{
	modem_info *info;

	if (!tty) {
		return;
	}
	info = (modem_info *) tty->driver_data;
	if (isdn_tty_paranoia_check(info, tty->name, "isdn_tty_flush_buffer")) {
		return;
	}
	isdn_tty_cleanup_xmit(info);
	info->xmit_count = 0;
	tty_wakeup(tty);
}