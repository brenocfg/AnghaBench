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
struct snd_msndmidi {int /*<<< orphan*/  dev; int /*<<< orphan*/ * substream_input; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {struct snd_msndmidi* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDEX_MIDI_IN_STOP ; 
 int /*<<< orphan*/  MSNDMIDI_MODE_BIT_INPUT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_msnd_disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_msnd_send_dsp_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_msndmidi_input_close(struct snd_rawmidi_substream *substream)
{
	struct snd_msndmidi *mpu;

	mpu = substream->rmidi->private_data;
	snd_msnd_send_dsp_cmd(mpu->dev, HDEX_MIDI_IN_STOP);
	clear_bit(MSNDMIDI_MODE_BIT_INPUT, &mpu->mode);
	mpu->substream_input = NULL;
	snd_msnd_disable_irq(mpu->dev);
	return 0;
}