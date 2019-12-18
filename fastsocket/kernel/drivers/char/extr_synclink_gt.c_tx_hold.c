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
struct tty_struct {int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct slgt_info {int /*<<< orphan*/  lock; TYPE_1__ params; scalar_t__ tx_enabled; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_stop (struct slgt_info*) ; 

__attribute__((used)) static void tx_hold(struct tty_struct *tty)
{
	struct slgt_info *info = tty->driver_data;
	unsigned long flags;

	if (sanity_check(info, tty->name, "tx_hold"))
		return;
	DBGINFO(("%s tx_hold\n", info->device_name));
	spin_lock_irqsave(&info->lock,flags);
	if (info->tx_enabled && info->params.mode == MGSL_MODE_ASYNC)
	 	tx_stop(info);
	spin_unlock_irqrestore(&info->lock,flags);
}