#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usbmidi_out_port {int /*<<< orphan*/  state; struct snd_rawmidi_substream* substream; } ;
struct snd_usb_midi {int /*<<< orphan*/  iface; TYPE_3__* endpoints; } ;
struct snd_rawmidi_substream {TYPE_4__* runtime; TYPE_1__* rmidi; } ;
struct TYPE_8__ {struct usbmidi_out_port* private_data; } ;
struct TYPE_7__ {TYPE_2__* out; } ;
struct TYPE_6__ {struct usbmidi_out_port* ports; } ;
struct TYPE_5__ {struct snd_usb_midi* private_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int MIDI_MAX_ENDPOINTS ; 
 int /*<<< orphan*/  STATE_UNKNOWN ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  substream_open (struct snd_rawmidi_substream*,int) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usbmidi_output_open(struct snd_rawmidi_substream *substream)
{
	struct snd_usb_midi* umidi = substream->rmidi->private_data;
	struct usbmidi_out_port* port = NULL;
	int i, j;
	int err;

	for (i = 0; i < MIDI_MAX_ENDPOINTS; ++i)
		if (umidi->endpoints[i].out)
			for (j = 0; j < 0x10; ++j)
				if (umidi->endpoints[i].out->ports[j].substream == substream) {
					port = &umidi->endpoints[i].out->ports[j];
					break;
				}
	if (!port) {
		snd_BUG();
		return -ENXIO;
	}
	err = usb_autopm_get_interface(umidi->iface);
	if (err < 0)
		return -EIO;
	substream->runtime->private_data = port;
	port->state = STATE_UNKNOWN;
	substream_open(substream, 1);
	return 0;
}