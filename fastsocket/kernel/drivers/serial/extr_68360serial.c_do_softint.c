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
struct tty_struct {int dummy; } ;
struct TYPE_3__ {struct tty_struct* tty; } ;
struct TYPE_4__ {int /*<<< orphan*/  event; TYPE_1__ port; } ;
typedef  TYPE_2__ ser_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  RS_EVENT_WRITE_WAKEUP ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void do_softint(void *private_)
{
	ser_info_t	*info = (ser_info_t *) private_;
	struct tty_struct	*tty;
	
	tty = info->port.tty;
	if (!tty)
		return;

	if (test_and_clear_bit(RS_EVENT_WRITE_WAKEUP, &info->event))
		tty_wakeup(tty);
}