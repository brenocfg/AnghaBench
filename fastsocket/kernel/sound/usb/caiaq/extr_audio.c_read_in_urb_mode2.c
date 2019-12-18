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
struct snd_usb_caiaqdev {int n_streams; int input_panic; int output_panic; int* audio_in_buf_pos; int /*<<< orphan*/ * period_in_count; struct snd_pcm_substream** sub_capture; scalar_t__ first_packet; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {char* dma_area; int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
 int BYTES_PER_SAMPLE_USB ; 
 unsigned char MAKE_CHECKBYTE (struct snd_usb_caiaqdev*,int,int) ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_in_urb_mode2(struct snd_usb_caiaqdev *dev,
			      const struct urb *urb,
			      const struct usb_iso_packet_descriptor *iso)
{
	unsigned char *usb_buf = urb->transfer_buffer + iso->offset;
	unsigned char check_byte;
	struct snd_pcm_substream *sub;
	int stream, i;

	for (i = 0; i < iso->actual_length;) {
		if (i % (dev->n_streams * BYTES_PER_SAMPLE_USB) == 0) {
			for (stream = 0;
			     stream < dev->n_streams;
			     stream++, i++) {
				if (dev->first_packet)
					continue;

				check_byte = MAKE_CHECKBYTE(dev, stream, i);

				if ((usb_buf[i] & 0x3f) != check_byte)
					dev->input_panic = 1;

				if (usb_buf[i] & 0x80)
					dev->output_panic = 1;
			}
		}
		dev->first_packet = 0;

		for (stream = 0; stream < dev->n_streams; stream++, i++) {
			sub = dev->sub_capture[stream];
			if (dev->input_panic)
				usb_buf[i] = 0;

			if (sub) {
				struct snd_pcm_runtime *rt = sub->runtime;
				char *audio_buf = rt->dma_area;
				int sz = frames_to_bytes(rt, rt->buffer_size);
				audio_buf[dev->audio_in_buf_pos[stream]++] =
					usb_buf[i];
				dev->period_in_count[stream]++;
				if (dev->audio_in_buf_pos[stream] == sz)
					dev->audio_in_buf_pos[stream] = 0;
			}
		}
	}
}