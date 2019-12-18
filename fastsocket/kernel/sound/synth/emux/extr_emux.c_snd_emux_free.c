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
struct snd_emux {struct snd_emux* name; struct snd_emux* voices; scalar_t__ sflist; int /*<<< orphan*/  voice_lock; int /*<<< orphan*/  tlist; scalar_t__ timer_active; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_delete_hwdep (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_delete_virmidi (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_detach_seq (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_detach_seq_oss (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_proc_free (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_sf_free (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_emux_free(struct snd_emux *emu)
{
	unsigned long flags;

	if (! emu)
		return -EINVAL;

	spin_lock_irqsave(&emu->voice_lock, flags);
	if (emu->timer_active)
		del_timer(&emu->tlist);
	spin_unlock_irqrestore(&emu->voice_lock, flags);

#ifdef CONFIG_PROC_FS
	snd_emux_proc_free(emu);
#endif
	snd_emux_delete_virmidi(emu);
#ifdef CONFIG_SND_SEQUENCER_OSS
	snd_emux_detach_seq_oss(emu);
#endif
	snd_emux_detach_seq(emu);

	snd_emux_delete_hwdep(emu);

	if (emu->sflist)
		snd_sf_free(emu->sflist);

	kfree(emu->voices);
	kfree(emu->name);
	kfree(emu);
	return 0;
}