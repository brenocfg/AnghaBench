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
typedef  TYPE_2__* ipmi_user_t ;
struct TYPE_5__ {TYPE_1__* intf; } ;
struct TYPE_4__ {int maintenance_mode; int /*<<< orphan*/  maintenance_mode_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipmi_get_maintenance_mode(ipmi_user_t user)
{
	int           mode;
	unsigned long flags;

	spin_lock_irqsave(&user->intf->maintenance_mode_lock, flags);
	mode = user->intf->maintenance_mode;
	spin_unlock_irqrestore(&user->intf->maintenance_mode_lock, flags);

	return mode;
}