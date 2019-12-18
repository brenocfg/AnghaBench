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
struct hdsp_midi {int /*<<< orphan*/  lock; struct snd_rawmidi_substream* input; int /*<<< orphan*/  id; int /*<<< orphan*/  hdsp; } ;
struct TYPE_2__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hdsp_flush_midi_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdsp_midi_input_open(struct snd_rawmidi_substream *substream)
{
	struct hdsp_midi *hmidi;

	hmidi = (struct hdsp_midi *) substream->rmidi->private_data;
	spin_lock_irq (&hmidi->lock);
	snd_hdsp_flush_midi_input (hmidi->hdsp, hmidi->id);
	hmidi->input = substream;
	spin_unlock_irq (&hmidi->lock);

	return 0;
}