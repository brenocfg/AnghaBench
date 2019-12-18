#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
struct snd_virmidi {int trigger; scalar_t__ seq_mode; TYPE_3__ event; int /*<<< orphan*/  client; int /*<<< orphan*/  parser; TYPE_1__* rdev; } ;
struct snd_rawmidi_substream {TYPE_2__* runtime; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int buffer_size; int avail; struct snd_virmidi* private_data; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 scalar_t__ SNDRV_SEQ_EVENT_NONE ; 
 scalar_t__ SNDRV_VIRMIDI_SEQ_DISPATCH ; 
 int SNDRV_VIRMIDI_SUBSCRIBE ; 
 int /*<<< orphan*/  in_atomic () ; 
 int snd_midi_event_encode (int /*<<< orphan*/ ,unsigned char*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  snd_midi_event_reset_encode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (struct snd_rawmidi_substream*,int) ; 
 int snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 scalar_t__ snd_seq_kernel_client_dispatch (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_virmidi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct snd_virmidi *vmidi = substream->runtime->private_data;
	int count, res;
	unsigned char buf[32], *pbuf;

	if (up) {
		vmidi->trigger = 1;
		if (vmidi->seq_mode == SNDRV_VIRMIDI_SEQ_DISPATCH &&
		    !(vmidi->rdev->flags & SNDRV_VIRMIDI_SUBSCRIBE)) {
			snd_rawmidi_transmit_ack(substream, substream->runtime->buffer_size - substream->runtime->avail);
			return;		/* ignored */
		}
		if (vmidi->event.type != SNDRV_SEQ_EVENT_NONE) {
			if (snd_seq_kernel_client_dispatch(vmidi->client, &vmidi->event, in_atomic(), 0) < 0)
				return;
			vmidi->event.type = SNDRV_SEQ_EVENT_NONE;
		}
		while (1) {
			count = snd_rawmidi_transmit_peek(substream, buf, sizeof(buf));
			if (count <= 0)
				break;
			pbuf = buf;
			while (count > 0) {
				res = snd_midi_event_encode(vmidi->parser, pbuf, count, &vmidi->event);
				if (res < 0) {
					snd_midi_event_reset_encode(vmidi->parser);
					continue;
				}
				snd_rawmidi_transmit_ack(substream, res);
				pbuf += res;
				count -= res;
				if (vmidi->event.type != SNDRV_SEQ_EVENT_NONE) {
					if (snd_seq_kernel_client_dispatch(vmidi->client, &vmidi->event, in_atomic(), 0) < 0)
						return;
					vmidi->event.type = SNDRV_SEQ_EVENT_NONE;
				}
			}
		}
	} else {
		vmidi->trigger = 0;
	}
}