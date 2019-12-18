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
struct mod_status {int /*<<< orphan*/  fls; } ;

/* Variables and functions */
 int /*<<< orphan*/  USU_MOD_FL_PRESENT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mod_status* stat ; 
 int /*<<< orphan*/  usu_lock ; 

void usb_usual_set_present(int type)
{
	struct mod_status *st;
	unsigned long flags;

	if (type <= 0 || type >= 3)
		return;
	st = &stat[type];
	spin_lock_irqsave(&usu_lock, flags);
	st->fls |= USU_MOD_FL_PRESENT;
	spin_unlock_irqrestore(&usu_lock, flags);
}