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
struct snd_opl3 {struct snd_hwdep* hwdep; int /*<<< orphan*/  sys_timer_lock; scalar_t__ sys_timer_status; int /*<<< orphan*/  tlist; } ;
struct snd_hwdep {int /*<<< orphan*/  open_wait; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_opl3_reset (struct snd_opl3*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void snd_opl3_synth_cleanup(struct snd_opl3 * opl3)
{
	unsigned long flags;
	struct snd_hwdep *hwdep;

	/* Stop system timer */
	spin_lock_irqsave(&opl3->sys_timer_lock, flags);
	if (opl3->sys_timer_status) {
		del_timer(&opl3->tlist);
		opl3->sys_timer_status = 0;
	}
	spin_unlock_irqrestore(&opl3->sys_timer_lock, flags);

	snd_opl3_reset(opl3);
	hwdep = opl3->hwdep;
	mutex_lock(&hwdep->open_mutex);
	hwdep->used--;
	mutex_unlock(&hwdep->open_mutex);
	wake_up(&hwdep->open_wait);
}