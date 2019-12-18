#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t snd_wavefront_mpu_id ;
struct TYPE_8__ {size_t output_mpu; int* mode; scalar_t__ istimer; int /*<<< orphan*/  virtual; int /*<<< orphan*/  timer; int /*<<< orphan*/  isvirtual; int /*<<< orphan*/ ** substream_output; } ;
typedef  TYPE_2__ snd_wavefront_midi_t ;
struct TYPE_7__ {TYPE_2__ midi; } ;
struct TYPE_9__ {TYPE_1__ wavefront; } ;
typedef  TYPE_3__ snd_wavefront_card_t ;

/* Variables and functions */
 int MPU401_MODE_OUTPUT ; 
 int MPU401_MODE_OUTPUT_TRIGGER ; 
 unsigned char WF_EXTERNAL_SWITCH ; 
 unsigned char WF_INTERNAL_SWITCH ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 size_t internal_mpu ; 
 scalar_t__ output_ready (TYPE_2__*) ; 
 int snd_rawmidi_transmit (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ snd_rawmidi_transmit_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_data (TYPE_2__*,unsigned char) ; 

__attribute__((used)) static void snd_wavefront_midi_output_write(snd_wavefront_card_t *card)
{
	snd_wavefront_midi_t *midi = &card->wavefront.midi;
	snd_wavefront_mpu_id  mpu;
	unsigned long flags;
	unsigned char midi_byte;
	int max = 256, mask = 1;
	int timeout;

	/* Its not OK to try to change the status of "virtuality" of
	   the MIDI interface while we're outputting stuff.  See
	   snd_wavefront_midi_{enable,disable}_virtual () for the
	   other half of this.  

	   The first loop attempts to flush any data from the
	   current output device, and then the second 
	   emits the switch byte (if necessary), and starts
	   outputting data for the output device currently in use.
	*/

	if (midi->substream_output[midi->output_mpu] == NULL) {
		goto __second;
	}

	while (max > 0) {

		/* XXX fix me - no hard timing loops allowed! */

		for (timeout = 30000; timeout > 0; timeout--) {
			if (output_ready (midi))
				break;
		}
	
		spin_lock_irqsave (&midi->virtual, flags);
		if ((midi->mode[midi->output_mpu] & MPU401_MODE_OUTPUT) == 0) {
			spin_unlock_irqrestore (&midi->virtual, flags);
			goto __second;
		}
		if (output_ready (midi)) {
			if (snd_rawmidi_transmit(midi->substream_output[midi->output_mpu], &midi_byte, 1) == 1) {
				if (!midi->isvirtual ||
					(midi_byte != WF_INTERNAL_SWITCH &&
					 midi_byte != WF_EXTERNAL_SWITCH))
					write_data(midi, midi_byte);
				max--;
			} else {
				if (midi->istimer) {
					if (--midi->istimer <= 0)
						del_timer(&midi->timer);
				}
				midi->mode[midi->output_mpu] &= ~MPU401_MODE_OUTPUT_TRIGGER;
				spin_unlock_irqrestore (&midi->virtual, flags);
				goto __second;
			}
		} else {
			spin_unlock_irqrestore (&midi->virtual, flags);
			return;
		}
		spin_unlock_irqrestore (&midi->virtual, flags);
	}

      __second:

	if (midi->substream_output[!midi->output_mpu] == NULL) {
		return;
	}

	while (max > 0) {

		/* XXX fix me - no hard timing loops allowed! */

		for (timeout = 30000; timeout > 0; timeout--) {
			if (output_ready (midi))
				break;
		}
	
		spin_lock_irqsave (&midi->virtual, flags);
		if (!midi->isvirtual)
			mask = 0;
		mpu = midi->output_mpu ^ mask;
		mask = 0;	/* don't invert the value from now */
		if ((midi->mode[mpu] & MPU401_MODE_OUTPUT) == 0) {
			spin_unlock_irqrestore (&midi->virtual, flags);
			return;
		}
		if (snd_rawmidi_transmit_empty(midi->substream_output[mpu]))
			goto __timer;
		if (output_ready (midi)) {
			if (mpu != midi->output_mpu) {
				write_data(midi, mpu == internal_mpu ?
							WF_INTERNAL_SWITCH :
							WF_EXTERNAL_SWITCH);
				midi->output_mpu = mpu;
			} else if (snd_rawmidi_transmit(midi->substream_output[mpu], &midi_byte, 1) == 1) {
				if (!midi->isvirtual ||
					(midi_byte != WF_INTERNAL_SWITCH &&
					 midi_byte != WF_EXTERNAL_SWITCH))
					write_data(midi, midi_byte);
				max--;
			} else {
			      __timer:
				if (midi->istimer) {
					if (--midi->istimer <= 0)
						del_timer(&midi->timer);
				}
				midi->mode[mpu] &= ~MPU401_MODE_OUTPUT_TRIGGER;
				spin_unlock_irqrestore (&midi->virtual, flags);
				return;
			}
		} else {
			spin_unlock_irqrestore (&midi->virtual, flags);
			return;
		}
		spin_unlock_irqrestore (&midi->virtual, flags);
	}
}