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
struct snd_usb_midi {int /*<<< orphan*/  iface; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_2__ {struct snd_usb_midi* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  substream_open (struct snd_rawmidi_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usbmidi_output_close(struct snd_rawmidi_substream *substream)
{
	struct snd_usb_midi* umidi = substream->rmidi->private_data;

	substream_open(substream, 0);
	usb_autopm_put_interface(umidi->iface);
	return 0;
}