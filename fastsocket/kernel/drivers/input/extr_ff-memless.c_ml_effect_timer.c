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
struct ml_device {int dummy; } ;
struct input_dev {int /*<<< orphan*/  event_lock; TYPE_1__* ff; } ;
struct TYPE_2__ {struct ml_device* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  ml_play_effects (struct ml_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ml_effect_timer(unsigned long timer_data)
{
	struct input_dev *dev = (struct input_dev *)timer_data;
	struct ml_device *ml = dev->ff->private;
	unsigned long flags;

	debug("timer: updating effects");

	spin_lock_irqsave(&dev->event_lock, flags);
	ml_play_effects(ml);
	spin_unlock_irqrestore(&dev->event_lock, flags);
}