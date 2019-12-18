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
struct soundscape {scalar_t__ midi_usage; int hw_in_use; int /*<<< orphan*/  fwlock; } ;
struct snd_hwdep {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct soundscape* get_hwdep_soundscape (struct snd_hwdep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sscape_hw_open(struct snd_hwdep * hw, struct file *file)
{
	register struct soundscape *sscape = get_hwdep_soundscape(hw);
	unsigned long flags;
	int err;

	spin_lock_irqsave(&sscape->fwlock, flags);

	if ((sscape->midi_usage != 0) || sscape->hw_in_use) {
		err = -EBUSY;
	} else {
		sscape->hw_in_use = 1;
		err = 0;
	}

	spin_unlock_irqrestore(&sscape->fwlock, flags);
	return err;
}