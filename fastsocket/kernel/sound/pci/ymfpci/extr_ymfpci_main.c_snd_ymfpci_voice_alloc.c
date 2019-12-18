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
struct snd_ymfpci_voice {int dummy; } ;
struct snd_ymfpci {int /*<<< orphan*/  voice_lock; } ;
typedef  enum snd_ymfpci_voice_type { ____Placeholder_snd_ymfpci_voice_type } snd_ymfpci_voice_type ;

/* Variables and functions */
 int EINVAL ; 
 int YMFPCI_PCM ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int voice_alloc (struct snd_ymfpci*,int,int,struct snd_ymfpci_voice**) ; 

__attribute__((used)) static int snd_ymfpci_voice_alloc(struct snd_ymfpci *chip,
				  enum snd_ymfpci_voice_type type, int pair,
				  struct snd_ymfpci_voice **rvoice)
{
	unsigned long flags;
	int result;
	
	if (snd_BUG_ON(!rvoice))
		return -EINVAL;
	if (snd_BUG_ON(pair && type != YMFPCI_PCM))
		return -EINVAL;
	
	spin_lock_irqsave(&chip->voice_lock, flags);
	for (;;) {
		result = voice_alloc(chip, type, pair, rvoice);
		if (result == 0 || type != YMFPCI_PCM)
			break;
		/* TODO: synth/midi voice deallocation */
		break;
	}
	spin_unlock_irqrestore(&chip->voice_lock, flags);	
	return result;		
}