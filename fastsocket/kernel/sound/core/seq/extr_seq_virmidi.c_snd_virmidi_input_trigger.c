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
struct snd_virmidi {int trigger; } ;
struct snd_rawmidi_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct snd_virmidi* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void snd_virmidi_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct snd_virmidi *vmidi = substream->runtime->private_data;

	if (up) {
		vmidi->trigger = 1;
	} else {
		vmidi->trigger = 0;
	}
}