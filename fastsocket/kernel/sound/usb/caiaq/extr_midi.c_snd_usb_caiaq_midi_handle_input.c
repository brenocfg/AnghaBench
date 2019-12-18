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
struct snd_usb_caiaqdev {int /*<<< orphan*/  midi_receive_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,char const*,int) ; 

void snd_usb_caiaq_midi_handle_input(struct snd_usb_caiaqdev *dev,
				     int port, const char *buf, int len)
{
	if (!dev->midi_receive_substream)
		return;

	snd_rawmidi_receive(dev->midi_receive_substream, buf, len);
}