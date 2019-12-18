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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct snd_emu10k1_midi {int /*<<< orphan*/  rx_enable; struct snd_emu10k1* emu; } ;
struct snd_emu10k1 {int dummy; } ;
struct TYPE_2__ {scalar_t__ private_data; } ;

/* Variables and functions */
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_emu10k1_intr_disable (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_intr_enable (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_emu10k1_midi_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct snd_emu10k1 *emu;
	struct snd_emu10k1_midi *midi = (struct snd_emu10k1_midi *)substream->rmidi->private_data;
	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		return;

	if (up)
		snd_emu10k1_intr_enable(emu, midi->rx_enable);
	else
		snd_emu10k1_intr_disable(emu, midi->rx_enable);
}