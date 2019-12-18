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
typedef  int uint8_t ;
struct snd_usb_midi_in_endpoint {int dummy; } ;

/* Variables and functions */
 int* snd_usbmidi_cin_length ; 
 int /*<<< orphan*/  snd_usbmidi_input_data (struct snd_usb_midi_in_endpoint*,int,int*,int) ; 

__attribute__((used)) static void snd_usbmidi_standard_input(struct snd_usb_midi_in_endpoint* ep,
				       uint8_t* buffer, int buffer_length)
{
	int i;

	for (i = 0; i + 3 < buffer_length; i += 4)
		if (buffer[i] != 0) {
			int cable = buffer[i] >> 4;
			int length = snd_usbmidi_cin_length[buffer[i] & 0x0f];
			snd_usbmidi_input_data(ep, cable, &buffer[i + 1], length);
		}
}