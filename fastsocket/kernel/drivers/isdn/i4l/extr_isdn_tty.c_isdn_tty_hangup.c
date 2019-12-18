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
struct TYPE_4__ {int flags; int /*<<< orphan*/  open_wait; int /*<<< orphan*/ * tty; scalar_t__ count; } ;
typedef  TYPE_1__ modem_info ;

/* Variables and functions */
 int ISDN_ASYNC_CALLOUT_ACTIVE ; 
 int ISDN_ASYNC_NORMAL_ACTIVE ; 
 scalar_t__ isdn_tty_paranoia_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isdn_tty_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isdn_tty_hangup(struct tty_struct *tty)
{
	modem_info *info = (modem_info *) tty->driver_data;

	if (isdn_tty_paranoia_check(info, tty->name, "isdn_tty_hangup"))
		return;
	isdn_tty_shutdown(info);
	info->count = 0;
	info->flags &= ~(ISDN_ASYNC_NORMAL_ACTIVE | ISDN_ASYNC_CALLOUT_ACTIVE);
	info->tty = NULL;
	wake_up_interruptible(&info->open_wait);
}