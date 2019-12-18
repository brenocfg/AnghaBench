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
struct snd_korg1212 {int idleMonitorOn; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERCOMMAND_DELAY ; 
 int /*<<< orphan*/  K1212_DB_SelectPlayMode ; 
 int /*<<< orphan*/  K1212_MODE_MonitorOn ; 
 int snd_korg1212_Send1212Command (struct snd_korg1212*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_korg1212_TurnOnIdleMonitor(struct snd_korg1212 *korg1212)
{
	unsigned long flags;
	int rc;

        udelay(INTERCOMMAND_DELAY);
	spin_lock_irqsave(&korg1212->lock, flags);
        korg1212->idleMonitorOn = 1;
        rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SelectPlayMode,
					  K1212_MODE_MonitorOn, 0, 0, 0);
        spin_unlock_irqrestore(&korg1212->lock, flags);
	return rc;
}