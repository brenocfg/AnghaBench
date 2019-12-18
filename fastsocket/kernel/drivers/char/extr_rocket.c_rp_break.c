#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_struct {struct r_port* driver_data; } ;
struct r_port {int /*<<< orphan*/  slock; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ rocket_paranoia_check (struct r_port*,char*) ; 
 int /*<<< orphan*/  sClrBreak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sSendBreak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rp_break(struct tty_struct *tty, int break_state)
{
	struct r_port *info = tty->driver_data;
	unsigned long flags;

	if (rocket_paranoia_check(info, "rp_break"))
		return -EINVAL;

	spin_lock_irqsave(&info->slock, flags);
	if (break_state == -1)
		sSendBreak(&info->channel);
	else
		sClrBreak(&info->channel);
	spin_unlock_irqrestore(&info->slock, flags);
	return 0;
}