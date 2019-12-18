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

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAS_PCM_INTRBITS ; 
 int /*<<< orphan*/  PCM_NON ; 
 int /*<<< orphan*/  pas_audio_reset (int) ; 
 int /*<<< orphan*/  pas_lock ; 
 int /*<<< orphan*/  pas_remove_intr (int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_busy ; 
 int /*<<< orphan*/  pcm_mode ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pas_audio_close(int dev)
{
	unsigned long   flags;

	DEB(printk("pas2_pcm.c: static void pas_audio_close(void)\n"));

	spin_lock_irqsave(&pas_lock, flags);

	pas_audio_reset(dev);
	pas_remove_intr(PAS_PCM_INTRBITS);
	pcm_mode = PCM_NON;

	pcm_busy = 0;
	spin_unlock_irqrestore(&pas_lock, flags);
}