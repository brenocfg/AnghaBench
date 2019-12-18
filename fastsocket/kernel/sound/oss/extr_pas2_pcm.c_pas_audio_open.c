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
 int EBUSY ; 
 int /*<<< orphan*/  PAS_PCM_INTRBITS ; 
 int open_mode ; 
 int /*<<< orphan*/  pas_lock ; 
 int pas_set_intr (int /*<<< orphan*/ ) ; 
 int pcm_busy ; 
 scalar_t__ pcm_count ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pas_audio_open(int dev, int mode)
{
	int             err;
	unsigned long   flags;

	DEB(printk("pas2_pcm.c: static int pas_audio_open(int mode = %X)\n", mode));

	spin_lock_irqsave(&pas_lock, flags);
	if (pcm_busy)
	{
		spin_unlock_irqrestore(&pas_lock, flags);
		return -EBUSY;
	}
	pcm_busy = 1;
	spin_unlock_irqrestore(&pas_lock, flags);

	if ((err = pas_set_intr(PAS_PCM_INTRBITS)) < 0)
		return err;


	pcm_count = 0;
	open_mode = mode;

	return 0;
}