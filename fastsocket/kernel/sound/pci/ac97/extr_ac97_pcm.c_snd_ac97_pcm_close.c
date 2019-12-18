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
struct snd_ac97_bus {int** used_slots; int /*<<< orphan*/  bus_lock; } ;
struct ac97_pcm {unsigned short aslots; int cur_dbl; size_t stream; struct snd_ac97_bus* bus; TYPE_1__* r; } ;
struct TYPE_2__ {int* rslots; int /*<<< orphan*/ * codec; } ;

/* Variables and functions */
 int get_slot_reg (struct ac97_pcm*,int,int,int) ; 
 int /*<<< orphan*/  snd_ac97_update_power (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int snd_ac97_pcm_close(struct ac97_pcm *pcm)
{
	struct snd_ac97_bus *bus;
	unsigned short slots = pcm->aslots;
	int i, cidx;

#ifdef CONFIG_SND_AC97_POWER_SAVE
	int r = pcm->cur_dbl;
	for (i = 3; i < 12; i++) {
		if (!(slots & (1 << i)))
			continue;
		for (cidx = 0; cidx < 4; cidx++) {
			if (pcm->r[r].rslots[cidx] & (1 << i)) {
				int reg = get_slot_reg(pcm, cidx, i, r);
				snd_ac97_update_power(pcm->r[r].codec[cidx],
						      reg, 0);
			}
		}
	}
#endif

	bus = pcm->bus;
	spin_lock_irq(&pcm->bus->bus_lock);
	for (i = 3; i < 12; i++) {
		if (!(slots & (1 << i)))
			continue;
		for (cidx = 0; cidx < 4; cidx++)
			bus->used_slots[pcm->stream][cidx] &= ~(1 << i);
	}
	pcm->aslots = 0;
	pcm->cur_dbl = 0;
	spin_unlock_irq(&pcm->bus->bus_lock);
	return 0;
}