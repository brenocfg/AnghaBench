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
struct vx_core {int clock_source; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_clock_source ) (struct vx_core*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct vx_core*,int) ; 
 int /*<<< orphan*/  vx_toggle_dac_mute (struct vx_core*,int) ; 

__attribute__((used)) static void vx_change_clock_source(struct vx_core *chip, int source)
{
	unsigned long flags;

	/* we mute DAC to prevent clicks */
	vx_toggle_dac_mute(chip, 1);
	spin_lock_irqsave(&chip->lock, flags);
	chip->ops->set_clock_source(chip, source);
	chip->clock_source = source;
	spin_unlock_irqrestore(&chip->lock, flags);
	/* unmute */
	vx_toggle_dac_mute(chip, 0);
}