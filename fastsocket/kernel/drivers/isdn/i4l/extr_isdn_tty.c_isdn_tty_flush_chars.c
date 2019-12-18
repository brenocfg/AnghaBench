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
struct TYPE_3__ {int /*<<< orphan*/  xmit_queue; scalar_t__ xmit_count; } ;
typedef  TYPE_1__ modem_info ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_TIMER_MODEMXMIT ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isdn_tty_paranoia_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isdn_tty_flush_chars(struct tty_struct *tty)
{
	modem_info *info = (modem_info *) tty->driver_data;

	if (isdn_tty_paranoia_check(info, tty->name, "isdn_tty_flush_chars"))
		return;
	if ((info->xmit_count) || !skb_queue_empty(&info->xmit_queue))
		isdn_timer_ctrl(ISDN_TIMER_MODEMXMIT, 1);
}