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
struct tty_struct {int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct slgt_info {int /*<<< orphan*/  lock; scalar_t__ tx_count; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  tx_active; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_load (struct slgt_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tx_start (struct slgt_info*) ; 

__attribute__((used)) static void tx_release(struct tty_struct *tty)
{
	struct slgt_info *info = tty->driver_data;
	unsigned long flags;

	if (sanity_check(info, tty->name, "tx_release"))
		return;
	DBGINFO(("%s tx_release\n", info->device_name));
	spin_lock_irqsave(&info->lock,flags);
	if (!info->tx_active && info->tx_count) {
		tx_load(info, info->tx_buf, info->tx_count);
	 	tx_start(info);
	}
	spin_unlock_irqrestore(&info->lock,flags);
}