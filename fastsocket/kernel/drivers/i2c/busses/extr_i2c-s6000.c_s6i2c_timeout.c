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
struct TYPE_2__ {scalar_t__ expires; } ;
struct s6i2c_if {scalar_t__ timeout_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; TYPE_1__ timeout_timer; } ;

/* Variables and functions */
 scalar_t__ POLL_TIMEOUT ; 
 int /*<<< orphan*/  S6_I2C_INTRMASK ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_wr16 (struct s6i2c_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  s6i2c_handle_interrupt (struct s6i2c_if*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void s6i2c_timeout(unsigned long data)
{
	struct s6i2c_if *iface = (struct s6i2c_if *)data;
	unsigned long flags;

	spin_lock_irqsave(&iface->lock, flags);
	s6i2c_handle_interrupt(iface);
	if (--iface->timeout_count > 0) {
		iface->timeout_timer.expires = jiffies + POLL_TIMEOUT;
		add_timer(&iface->timeout_timer);
	} else {
		complete(&iface->complete);
		i2c_wr16(iface, S6_I2C_INTRMASK, 0);
	}
	spin_unlock_irqrestore(&iface->lock, flags);
}