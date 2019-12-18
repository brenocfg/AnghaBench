#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_rawmidi_substream {TYPE_2__* rmidi; } ;
typedef  size_t snd_wavefront_mpu_id ;
struct TYPE_10__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct TYPE_9__ {int* mode; int /*<<< orphan*/  virtual; int /*<<< orphan*/  istimer; TYPE_4__ timer; } ;
typedef  TYPE_3__ snd_wavefront_midi_t ;
typedef  int /*<<< orphan*/  snd_wavefront_card_t ;
struct TYPE_8__ {TYPE_1__* card; int /*<<< orphan*/ * private_data; } ;
struct TYPE_7__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int MPU401_MODE_OUTPUT_TRIGGER ; 
 int /*<<< orphan*/  add_timer (TYPE_4__*) ; 
 TYPE_3__* get_wavefront_midi (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  init_timer (TYPE_4__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  snd_wavefront_midi_output_timer ; 
 int /*<<< orphan*/  snd_wavefront_midi_output_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_wavefront_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	if (substream == NULL || substream->rmidi == NULL) 
	        return;

	if (substream->rmidi->private_data == NULL)
	        return;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->private_data);

	if ((midi = get_wavefront_midi (substream)) == NULL) {
		return;
	}

	spin_lock_irqsave (&midi->virtual, flags);
	if (up) {
		if ((midi->mode[mpu] & MPU401_MODE_OUTPUT_TRIGGER) == 0) {
			if (!midi->istimer) {
				init_timer(&midi->timer);
				midi->timer.function = snd_wavefront_midi_output_timer;
				midi->timer.data = (unsigned long) substream->rmidi->card->private_data;
				midi->timer.expires = 1 + jiffies;
				add_timer(&midi->timer);
			}
			midi->istimer++;
			midi->mode[mpu] |= MPU401_MODE_OUTPUT_TRIGGER;
		}
	} else {
		midi->mode[mpu] &= ~MPU401_MODE_OUTPUT_TRIGGER;
	}
	spin_unlock_irqrestore (&midi->virtual, flags);

	if (up)
		snd_wavefront_midi_output_write((snd_wavefront_card_t *)substream->rmidi->card->private_data);
}