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
struct snd_seq_device {struct snd_emux* driver_data; int /*<<< orphan*/  card; } ;
struct snd_emux {int max_voices; int num_ports; int pitch_shift; int midi_ports; int midi_devidx; int hwdep_idx; scalar_t__ linear_panning; int /*<<< orphan*/  memhdr; struct snd_emu10k1* hw; } ;
struct snd_emu10k1_synth_arg {int seq_ports; int max_voices; int /*<<< orphan*/  index; struct snd_emu10k1* hwptr; } ;
struct snd_emu10k1 {int /*<<< orphan*/  voice_lock; int /*<<< orphan*/  get_synth_voice; struct snd_emux* synth; scalar_t__ audigy; int /*<<< orphan*/  memhdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct snd_emu10k1_synth_arg* SNDRV_SEQ_DEVICE_ARGPTR (struct snd_seq_device*) ; 
 int /*<<< orphan*/  snd_emu10k1_ops_setup (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emu10k1_synth_get_voice ; 
 int /*<<< orphan*/  snd_emux_free (struct snd_emux*) ; 
 scalar_t__ snd_emux_new (struct snd_emux**) ; 
 scalar_t__ snd_emux_register (struct snd_emux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_emu10k1_synth_new_device(struct snd_seq_device *dev)
{
	struct snd_emux *emux;
	struct snd_emu10k1 *hw;
	struct snd_emu10k1_synth_arg *arg;
	unsigned long flags;

	arg = SNDRV_SEQ_DEVICE_ARGPTR(dev);
	if (arg == NULL)
		return -EINVAL;

	if (arg->seq_ports <= 0)
		return 0; /* nothing */
	if (arg->max_voices < 1)
		arg->max_voices = 1;
	else if (arg->max_voices > 64)
		arg->max_voices = 64;

	if (snd_emux_new(&emux) < 0)
		return -ENOMEM;

	snd_emu10k1_ops_setup(emux);
	hw = arg->hwptr;
	emux->hw = hw;
	emux->max_voices = arg->max_voices;
	emux->num_ports = arg->seq_ports;
	emux->pitch_shift = -501;
	emux->memhdr = hw->memhdr;
	/* maximum two ports */
	emux->midi_ports = arg->seq_ports < 2 ? arg->seq_ports : 2;
	/* audigy has two external midis */
	emux->midi_devidx = hw->audigy ? 2 : 1;
	emux->linear_panning = 0;
	emux->hwdep_idx = 2; /* FIXED */

	if (snd_emux_register(emux, dev->card, arg->index, "Emu10k1") < 0) {
		snd_emux_free(emux);
		return -ENOMEM;
	}

	spin_lock_irqsave(&hw->voice_lock, flags);
	hw->synth = emux;
	hw->get_synth_voice = snd_emu10k1_synth_get_voice;
	spin_unlock_irqrestore(&hw->voice_lock, flags);

	dev->driver_data = emux;

	return 0;
}