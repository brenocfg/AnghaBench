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
struct snd_seq_device {struct snd_emux* driver_data; } ;
struct snd_emux {struct snd_emu10k1* hw; } ;
struct snd_emu10k1 {int /*<<< orphan*/  voice_lock; int /*<<< orphan*/ * get_synth_voice; int /*<<< orphan*/ * synth; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_emux_free (struct snd_emux*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_emu10k1_synth_delete_device(struct snd_seq_device *dev)
{
	struct snd_emux *emux;
	struct snd_emu10k1 *hw;
	unsigned long flags;

	if (dev->driver_data == NULL)
		return 0; /* not registered actually */

	emux = dev->driver_data;

	hw = emux->hw;
	spin_lock_irqsave(&hw->voice_lock, flags);
	hw->synth = NULL;
	hw->get_synth_voice = NULL;
	spin_unlock_irqrestore(&hw->voice_lock, flags);

	snd_emux_free(emux);
	return 0;
}