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
struct snd_korg1212 {scalar_t__ dsp_stop_is_processed; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  snd_korg1212_SendStop (struct snd_korg1212*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void snd_korg1212_SendStopAndWait(struct snd_korg1212 *korg1212)
{
	unsigned long flags;
	spin_lock_irqsave(&korg1212->lock, flags);
	korg1212->dsp_stop_is_processed = 0;
	snd_korg1212_SendStop(korg1212);
	spin_unlock_irqrestore(&korg1212->lock, flags);
	wait_event_timeout(korg1212->wait, korg1212->dsp_stop_is_processed, (HZ * 3) / 2);
}