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
struct usb_iso_packet_descriptor {int offset; int actual_length; } ;
struct urb {unsigned char* transfer_buffer; } ;
struct snd_usb_caiaqdev {int n_streams; int* audio_in_buf_pos; int /*<<< orphan*/ * period_in_count; struct snd_pcm_substream** sub_capture; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {char* dma_area; int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
 scalar_t__ all_substreams_zero (struct snd_pcm_substream**) ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_in_urb_mode0(struct snd_usb_caiaqdev *dev,
			      const struct urb *urb,
			      const struct usb_iso_packet_descriptor *iso)
{
	unsigned char *usb_buf = urb->transfer_buffer + iso->offset;
	struct snd_pcm_substream *sub;
	int stream, i;

	if (all_substreams_zero(dev->sub_capture))
		return;

	for (i = 0; i < iso->actual_length;) {
		for (stream = 0; stream < dev->n_streams; stream++, i++) {
			sub = dev->sub_capture[stream];
			if (sub) {
				struct snd_pcm_runtime *rt = sub->runtime;
				char *audio_buf = rt->dma_area;
				int sz = frames_to_bytes(rt, rt->buffer_size);
				audio_buf[dev->audio_in_buf_pos[stream]++]
					= usb_buf[i];
				dev->period_in_count[stream]++;
				if (dev->audio_in_buf_pos[stream] == sz)
					dev->audio_in_buf_pos[stream] = 0;
			}
		}
	}
}